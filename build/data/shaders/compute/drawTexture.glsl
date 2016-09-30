#version 430

layout (binding=1, rgba8) uniform image2D difIn;
layout (binding=2, rgba8) uniform image2D norIn;
layout (binding=3, rgba8) readonly uniform image2D difMat;
layout (binding=4, rgba8) readonly uniform image2D norMat;

uniform vec2 cursor; //3D position of cursor
uniform vec4 rect; //3D rect
uniform vec2 texSize; //2D integer texture size
uniform vec2 texScale; //material.scale

layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;


void main() {
	ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
	ivec2 pos2 = ivec2(gl_GlobalInvocationID.xy*texScale);
	pos2.x%=int(texSize.x);
	pos2.y%=int(texSize.y);

	vec2 phi = vec2(pos.x, pos.y)/texSize;
	vec2 theta = vec2(rect.z-rect.x, rect.w-rect.y);
	vec2 pixelPos = phi*theta + vec2(rect.x, rect.y);
	float dist = clamp(1.0-length(cursor-pixelPos), 0.0, 1.0);
	//dist = length(phi);

	vec4 c = imageLoad(difIn, pos);
	vec4 n = imageLoad(norIn, pos);
	vec4 c2 = imageLoad(difMat, pos2);
	vec4 n2 = imageLoad(norMat, pos2);

	imageStore( difIn, pos, c2*(dist) + c*(1.0-dist) );
	imageStore( norIn, pos, n2*(dist) + n*(1.0-dist) );
}

