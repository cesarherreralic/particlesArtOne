#version 440

in vec4 velocity;
in vec2 screenPosition;
in float radius;

out vec4 fs_color;


const float threshold = 0.3f;

void main()
{
	vec2 pixelPos = gl_FragCoord.xy;
	float dist = distance(pixelPos, screenPosition);
	float aRadius = radius * 720;
	vec3 aColor = vec3(1.0f);

    if (dist > aRadius){
		discard;
	}

	float gradient = 1.0f - (dist / aRadius);

    float d = dist / aRadius;
    vec3 color = mix(aColor.rgb, vec3(0.0f), step(1.0-threshold, d));

    fs_color = vec4(color, gradient);

}
