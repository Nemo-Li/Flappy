#version 320 es
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
  gl_Position = vPosition;
  TexCoord = aTexCoord;
}