#version 440

#define PI 3.1415926535897932384626433832795

// Process particles in blocks of 128
layout (local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

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

const float gravity = 0.f;
vec4 vector_down = vec4(0.f,-1.f,0.f, 0.f); // direction of gravity (floor)

// handle collision with borders
float collisionDamping = 0.9f;
float boundY = 1.f;
float boundX = 1.f;
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

float pressureMultiplier = 0.5f;
float targetDensity = 2.75f;

float ConvertDensityToPressure(float density){
	float densityError = density - targetDensity;
	float pressure = densityError * pressureMultiplier;
	return pressure;
}

vec2 CalculatePressureForce(uint index){
	vec2 pressureForce = vec2(0.f, 0.f);
	vec2 samplePoint = particles[index].position.xy;

	// loop over all particles
	for(int i=0; i < particles.length(); ++i)
	{
		if (index == i) continue;

		vec2 position = particles[i].position.xy;
		vec2 offset = position - samplePoint;
		float dst = length(offset);
		vec2 dir = dst == 0 ? vec2(0.f, 1.f) : offset / dst;
		float smoothingRadius = particles[i].extra.x;
		float mass = particles[i].extra.y;
		float slope = SmoothingKernelDerivative(dst, smoothingRadius);
		float density = particles[i].extra.w;
		pressureForce += -ConvertDensityToPressure(density) * dir * mass * slope / density;
	}
	return pressureForce;
}

void main()
{
	uint idx = gl_GlobalInvocationID.x;

	float dt = time * 6;

	vec4 velocity = particles[idx].velocity;
	vec4 position = particles[idx].position;

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

	vec2 pressureForce = CalculatePressureForce(idx);
	float density = particles[idx].extra[3];
	vec2 pressureAcceleration = pressureForce / density;

	particles[idx].position = position;	
	//particles[idx].velocity = velocity + (vec4(pressureAcceleration, 0.f, 0.f)* dt);
	particles[idx].velocity = (vec4(pressureAcceleration, 0.f, 0.f)* dt);

}