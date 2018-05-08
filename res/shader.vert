#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 VertexTexCoord;
layout (location = 2) in vec3 VertexNormal;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 ProjectionMatrix;
uniform mat4 model;
uniform mat4 view;
uniform mat3 NormalMatrix;

void main()
{
TexCoord = VertexTexCoord;
Normal = normalize( NormalMatrix * VertexNormal);
Position = vec3( model * vec4(VertexPosition,1.0));
gl_Position = ProjectionMatrix * view * vec4(VertexPosition,1.0);
}