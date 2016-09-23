#version 430

in vec3 pos;
in vec3 tan;
in vec3 btan;
in vec3 nor;
in vec2 tex;

uniform mat4 modelview;
uniform mat4 projection;

out vdata {
	vec3 pos;
	vec2 tex;
} vOut;

out matdata {
	vec3 tan;
	vec3 btan;
	vec3 nor;
} matOut;


void main(void) {
	matOut.tan = mat3(modelview)*tan;
	matOut.btan = mat3(modelview)*btan;
	matOut.nor = mat3(modelview)*nor;
	vOut.pos = (modelview*vec4(pos, 1.0)).xyz;
	vOut.tex = tex;
	gl_Position = projection*modelview*vec4(pos.xyz, 1.0);
}
