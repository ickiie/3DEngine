#version 430 core 

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 fs_color;

uniform float scale;
uniform mat4 model;
uniform mat4 view;

void main()
{
	fs_color = color;
	//fs_texcoord = texcoord;
    gl_Position = view * model * vec4(position * scale, 1.0);
}