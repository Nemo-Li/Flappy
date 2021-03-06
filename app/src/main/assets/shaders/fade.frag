#version 310 es
precision mediump float;

layout (location = 0) out vec4 color;

uniform float time;

void main()
{
	if (time > 1.0)
		discard;
	color = vec4(1.0, 1.0, 1.0, 1.0 - time);
}