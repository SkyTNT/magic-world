#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 TexCoord;

out vec2 mTexCoord;

uniform mat4 posmat;
uniform int type;//0 is rectangle,1 is text

void main()
{
    if(type==1){
        mTexCoord=vec2(TexCoord.x,1-TexCoord.y);
    }else{
        mTexCoord=TexCoord;
    }

    gl_Position = posmat*vec4(position,-1,1);
}
