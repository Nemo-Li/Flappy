#version 310 es
#extension GL_EXT_shader_io_blocks : enable

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tc;

out DATA
{
	vec2 tc;
} vs_out;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix;
uniform mat4 ml_matrix;

void main()
{
	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
	vs_out.tc = tc;
}