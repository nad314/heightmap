#version 430

layout (binding=1, rgba8) uniform image2D difIn;
layout (binding=2, rgba8) uniform image2D norIn;

uniform sampler2D matDiffuse;
uniform sampler2D matNormal;
uniform vec2 matScale; //material.scale

uniform vec2 cursor; //3D position of cursor
uniform vec2 brush; //(radius, intensity)
uniform vec4 rect; //3D rect
uniform vec2 texSize; //2D integer texture size
uniform vec2 chunkPos; //xy position of the chunk

layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;


void main() {
	ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
	vec2 pos2 = vec2(gl_GlobalInvocationID.xy)/512.0*matScale + chunkPos*matScale;

	vec2 phi = vec2(pos.x, pos.y)/texSize;
	vec2 theta = vec2(rect.z-rect.x, rect.w-rect.y);
	vec2 pixelPos = phi*theta + vec2(rect.x, rect.y);
	float dist = clamp((1.0-length(cursor-pixelPos)/brush.x)*brush.y, 0.0, 1.0);

	vec4 c = imageLoad(difIn, pos);
	vec4 n = imageLoad(norIn, pos);
	vec4 c2 = texture2D(matDiffuse, pos2);
	vec4 n2 = texture2D(matNormal, pos2);

	imageStore( difIn, pos, c2*(dist) + c*(1.0-dist) );
	imageStore( norIn, pos, n2*(dist) + n*(1.0-dist) );
}

