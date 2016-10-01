#version 430

in vec3 pos;

uniform mat4 view;
uniform mat4 proj;

out vData {
	vec3 p;
} vOut;

void main(void)
{
	vOut.p = pos;
	gl_Position = proj*view*vec4(pos,1.0);
}
