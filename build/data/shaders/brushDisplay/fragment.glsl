#version 430

uniform vec3 s;
uniform float r;

in vData {
	vec3 p;
} vIn;


out vec4 fragColor;


void main(void)
{
	float dist = length( vIn.p - s );
	float delta = fwidth(dist);
	float alpha = smoothstep(r-delta*1.5, r-delta, dist) * smoothstep(r, r-delta, dist);
	fragColor = vec4(vec3(0.8), alpha);
}
 
 