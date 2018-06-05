#version 330 core

in vec2 mTexCoord;
out vec4 color;
uniform sampler2D mTexture;
uniform vec4 useColor;
uniform int useTexture;
uniform int type;

void main()
{
    color=vec4(1,1,1,1);
    if(useTexture==1){
        color *= texture(mTexture,mTexCoord);
        if(type==1)color=vec4(1,1,1,color.r);
    }
    color*=useColor;
}
