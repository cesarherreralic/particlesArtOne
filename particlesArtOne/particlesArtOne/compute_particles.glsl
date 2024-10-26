#version 440

#define PI 3.1415926535897932384626433832795

// Process particles in blocks of 256
layout (local_size_x = 1024, local_size_y = 1, local_size_z = 1) in;

// Define el buffer con el binding explícito en el shader
struct Particle {
    vec4 position;
    vec4 velocity;
	vec4 extra;
};

layout(std430, binding = 0) buffer ParticlesBuffer {
    Particle particles[];
};

uniform float time;
uniform float gravity;
uniform float collisionDamping;
uniform float pressureMultiplier;
uniform float targetDensity;
uniform float speed;

//const float gravity = 0.f;
vec4 vector_down = vec4(0.f,-1.f,0.f, 0.f); // direction of gravity (floor)

// handle collision with borders
//float collisionDamping = 0.9f;
float boundY = 0.99f;
float boundX = 0.99f;
float verticalSurfaceTolerance = 0.05f;

float SmoothingKernel(float radius, float dst){
	float volume = PI * pow(radius, 8) / 4;
	float value = max(0.f, radius*radius - dst*dst);
	return value * value * value / volume;
}

float SmoothingKernelDerivative(float dst, float radius){
	if (dst >= radius) return 0.f;

	float f = radius * radius - dst * dst;
	float scale = -24 / (PI * pow(radius, 8));
	return scale * dst * f * f;
}

float CalculateDensity(vec2 samplePoint){
	float density = 0.f;
	const float mass = 1.f;

	// loop over all particles
	for(int i=0; i<particles.length(); ++i)
	{
		vec2 position = particles[i].position.xy;
		float dst = length(position - samplePoint);
		float smoothingRadius = particles[i].extra[0];
		float mass = particles[i].extra[1];
		float influence = SmoothingKernel(smoothingRadius, dst);
		density += mass * influence;
	}
	return density;
}

float CalculateProperty(vec2 samplePoint){
	float property = 0.f;
	
	// loop over all particles
	for(int i=0; i<particles.length(); ++i)
	{
		vec2 position = particles[i].position.xy;
		float dst = length(position - samplePoint);
		float smoothingRadius = particles[i].extra[0];
		float mass = particles[i].extra[1];
		float influence = SmoothingKernel(smoothingRadius, dst);
		float density = CalculateDensity(position);
		float particleProperty = particles[i].extra[2];
		property += particleProperty * mass * influence / density;
	}
	return property;
}

float ConvertDensityToPressure(float density){
	float densityError = density - targetDensity;
	float pressure = densityError * pressureMultiplier;
	return pressure;
}

vec2 CalculatePressureForce(Particle particle, uint index){
	vec2 pressureForce = vec2(0.f, 0.f);
	//vec2 samplePoint = particles[index].position.xy;
	vec2 samplePoint = particle.position.xy;

	// loop over all particles
	for(int i=0; i < particles.length(); ++i)
	{
		if (index == i) continue;

		vec2 position = particles[i].position.xy;
		vec2 offset = position - samplePoint;
		float dst = length(offset);
		vec2 dir = dst <= 0 ? vec2(0.f, 1.f) : offset / dst;
		float smoothingRadius = particles[i].extra.x;
		float mass = particles[i].extra.y;
		float slope = SmoothingKernelDerivative(dst, smoothingRadius);
		float density = particles[i].extra[3];
		//float density = CalculateDensity(particles[i].position.xy);
		pressureForce += -ConvertDensityToPressure(density) * dir * mass * slope / density;
	}
	return pressureForce;
}

void handleBorderCollision(uint idx){
	
	vec4 currentPosition = particles[idx].position;
	vec4 currentVelocity = particles[idx].velocity;
	vec4 currentExtra = particles[idx].extra;

	float dt = time * speed;

	vec4 position = currentPosition;
	vec4 velocity = currentVelocity;

	velocity += vector_down * gravity * dt;
	position += velocity * dt;

	//if (abs(velocity.y) < 0.05f && position.y <= floorY)
	//{
	//	velocity.x = 0.f;
	//}

	if (abs(position.x) >= boundX)
	{
		position.x = boundX * sign(position.x);
		velocity.x = -velocity.x * collisionDamping;
	}

	if (abs(position.y) >= boundY)
	{
		position.y = boundY * sign(position.y);
		velocity.y = -velocity.y * collisionDamping;

		bool isNearVerticalSurface = abs(velocity.y) < verticalSurfaceTolerance;
		bool theresGravity = gravity > 0.f;
		
		if (isNearVerticalSurface && theresGravity) {
			velocity.y = 0.0f;
			velocity.x = 0.0f;
        }
	}

	particles[idx].position = position;
	particles[idx].velocity = velocity;
	particles[idx].extra = currentExtra; // This one has no changes

}

void handleParticleToParticleCollision(uint idx){

	Particle particle1 = particles[idx];
	float m1 = particle1.extra[1];
	vec2 v1 = particle1.velocity.xy;
	float radius = particle1.extra[0];

	for(int i=0; i < particles.length(); ++i)
	{
		if (i == idx) continue;

		Particle particle2 = particles[i];

		float currentRadius = particle2.extra[0];

		if (distance(particle1.position.xy, particle2.position.xy) <= (currentRadius + radius)*10 ){
		
			float m2 = particles[i].extra[1];

			vec2 n = vec2(particle2.position.x - particle1.position.x, particle2.position.y - particle1.position.y);

			vec2 un = n / max(sqrt(n.x*n.x + n.y*n.y), 0.0001f);

			vec2 ut = vec2(-un.y, un.x);

			vec2 v2 = particle2.velocity.xy;

			float v1n = dot(un, v1);
			float v1t = dot(ut, v1);
			float v2n = dot(un, v2);
			float v2t = dot(ut, v2);

			v1n = (v1n * (m1 - m2) + 2*m2*v2n)/max((m1+m2), 0.0001f);
			v2n = (v2n * (m2 - m1) + 2*m1*v1n)/max((m1+m2), 0.0001f);

			vec2 vv1n = v1n * un;
			vec2 vv1t = v1t * ut;

			vec2 vv2n = v2n * un;
			vec2 vv2t = v2t * ut;

			vec2 finalVelocity1 = vv1n + vv1t;
			vec2 finalVelocity2 = vv2n + vv2t;
	
			particles[idx].velocity = vec4(finalVelocity1, vec2(0.f));
			particles[i].velocity = vec4(finalVelocity2, vec2(0.f));
		}

	}

}

void addGravity(uint idx){
	//uint pxPerM = 50;
	//uint fps = 60;
	float dt = time * speed;
	particles[idx].velocity += vector_down * (gravity /100) * dt;
	//particles[idx].velocity.y += gravity*9.8/fps*fps*pxPerM;
}

void handleWallCollision(uint idx){
	float radius = particles[idx].extra[0];
	if (particles[idx].position.x + radius <= -1.3f || particles[idx].position.x + radius >= 1.3f) {
		particles[idx].velocity.x = -collisionDamping*particles[idx].velocity.x;
		particles[idx].position.x += -sign(particles[idx].position.x)*(0.003f);
	}

	if (particles[idx].position.y + radius <= -0.98f || particles[idx].position.y + radius >= 0.98f) {
		particles[idx].velocity.y = -collisionDamping*particles[idx].velocity.y;
		particles[idx].position.y += -sign(particles[idx].position.y)*(0.003f);
	}
}

vec2 ballHitVelocity(uint idx1, uint idx2){
	Particle b1 = particles[idx1];
	Particle b2 = particles[idx2];
	float mRatio = (collisionDamping+1.f)*b2.extra[1]/(b1.extra[1]+b2.extra[1]);
	vec2 vDiff = b1.velocity.xy - b2.velocity.xy;
	vec2 rDiff = b1.position.xy - b2.position.xy;
	vec2 proj = (dot(vDiff, rDiff)/((rDiff[0]*rDiff[0]) + (rDiff[1]*rDiff[1])))*rDiff;
	return b1.velocity.xy - (proj*mRatio);
}

bool isHit(uint idx1, uint idx2){
	float dist = distance(particles[idx1].position.xy, particles[idx2].position.xy);
	return dist <= particles[idx1].extra[0] + particles[idx2].extra[0] + 0.1f;
}

void main()
{
	uint idx = gl_GlobalInvocationID.x;

	float dt = time * speed;

	for(int i=0; i < particles.length(); ++i)
	{
		if (idx == i) continue;

		if (isHit(idx, i)){
			vec2 v1 = ballHitVelocity(idx, i);
			vec2 v2 = ballHitVelocity(i, idx);

			particles[idx].velocity = vec4(v1, 0.f, 0.f);
			particles[i].velocity = vec4(v2, 0.f, 0.f);
		}
	}

	for(int i=0; i < particles.length(); ++i)
	{
		addGravity(i);
		handleWallCollision(i);
		particles[i].position += particles[i].velocity * speed/100;
	}

	//handleBorderCollision(idx);
	
	//handleParticleToParticleCollision(idx);

	vec2 pressureForce = CalculatePressureForce(particles[idx], idx);
	float density = particles[idx].extra[3];
	vec2 pressureAcceleration = pressureForce / max(density, 0.3f);

	//particles[idx].position = particles[idx].position;
	particles[idx].velocity += (vec4(pressureAcceleration, 0.f, 0.f));
	//particles[idx].velocity += (vec4(pressureAcceleration, 0.f, 0.f) * dt);
	
	//particles[idx].velocity = (vec4(pressureAcceleration, 0.f, 0.f));

	//handleParticleToParticleCollision(idx);

}