#version 440


// Define el buffer con el binding explícito en el shader
struct Particle {
    vec4 position;
    vec4 velocity;
	vec4 extra;
};
layout(std430, binding = 0) buffer ParticlesBuffer {
    Particle particles[];
};

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform vec2 resolution;

uniform float time;

out vec4 position;
out vec4 velocity;
out vec2 screenPosition;
out float radius;

vec2 normalizePosition(vec2 position) {
    vec2 normalizedPosition = (position / resolution) * 2.0 - vec2(1.0, 1.0);
    return normalizedPosition;
}

void main()
{

	Particle particle = particles[gl_VertexID];
	velocity = particle.velocity;

	vec2 normalizedPosition = normalizePosition(particle.position.xy);
	
	vec4 clipSpacePos = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(normalizedPosition, 0.0f, 1.f);
	vec2 ndcPosition = clipSpacePos.xy / clipSpacePos.w;

	screenPosition = (ndcPosition * 0.5f + 0.5f) * resolution;
	radius = particle.extra[0];
	gl_PointSize = radius*2;
	//gl_PointSize = max(30.0f, 1.f);
	gl_Position = clipSpacePos;
}