#version 430
in vdata {
	vec3 pos;
	vec2 tex;
} vIn;

in matdata {
	vec3 tan;
	vec3 btan;
	vec3 nor;
} matIn;

out vec4 fragColor;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform float scale;

void main(void) {
	vec3 lightDir = normalize(vec3(0.5f, 0.5f, 0.0f)-vIn.pos.xyz);
	mat3 tsm = mat3(normalize(matIn.tan), normalize(matIn.btan), normalize(matIn.nor));
	vec3 color = texture2D(diffuseMap, vIn.tex*scale).xyz;
	vec3 normal = texture2D(normalMap, vIn.tex*scale).xyz*2.0 - 1.0;
	normal = tsm*normalize(normal);
	float diff = dot(normal, lightDir)*.8;
	float specular = pow(clamp(dot(reflect(-lightDir, normal), (-vIn.pos.xyz)), 0.0, 1.0), 4.0)*.05;
	if (diff < 0.0)
		specular = 0;
	fragColor = vec4(color*smoothstep(0.0f, 1.0f, clamp(diff + specular +.15, 0, 1)), 1.0);
	fragColor = 1.0-exp2(-fragColor*2.0f);
	fragColor.a = 1.0;

}
