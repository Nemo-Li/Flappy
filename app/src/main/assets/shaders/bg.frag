#version 310 es
#extension GL_EXT_shader_io_blocks : enable
precision mediump float;

layout (location = 0) out vec4 color;

in DATA
{
	vec2 tc;
	vec3 position;
} fs_in;

uniform vec2 bird;
uniform sampler2D tex;

void main()
{
	color = texture(tex, fs_in.tc);
	color *= 2.0 / (length(bird - fs_in.position.xy) + 2.5) + 0.5;
}