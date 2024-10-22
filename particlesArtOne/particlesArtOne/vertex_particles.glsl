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

void main()
{

	Particle particle = particles[gl_VertexID];
	velocity = particle.velocity;
	
	vec4 clipSpacePos = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(particle.position.xy, 0.0f, 1.f);
	vec2 ndcPosition = clipSpacePos.xy / clipSpacePos.w;

	screenPosition = (ndcPosition * 0.5f + 0.5f) * resolution;
	radius = particle.extra[0] * 5;
	gl_PointSize = max(30.0f, 1.f);
	gl_Position = clipSpacePos;
}