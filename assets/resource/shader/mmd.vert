#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 TexCoord;
out vec3 fragPos;
out vec3 mNormal;
out vec2 mTexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    fragPos=vec3(model*vec4(position, 1.0));
    mTexCoord=TexCoord;
    mNormal=vec3(model*vec4(normal, 1.0));
    gl_Position = proj*view*vec4(fragPos,1.0);

}
