#version 430

in vec3 pos;

uniform mat4 modelview;
uniform mat4 projection;

void main(void) {
	gl_Position = projection*modelview*vec4(pos, 1.0);
}
