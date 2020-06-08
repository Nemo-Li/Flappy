#version 310 es
#extension GL_EXT_shader_io_blocks : enable
precision mediump float;

layout (location = 0) out vec4 color;

in DATA
{
	vec2 tc;
	vec3 position;
} fs_in;

uniform sampler2D tex;

void main()
{
	color = texture(tex, fs_in.tc);
}