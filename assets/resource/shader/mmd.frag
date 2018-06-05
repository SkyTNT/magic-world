#version 330 core

in vec2 mTexCoord;
in vec3 fragPos;
in vec3 mNormal;
out vec4 color;
uniform sampler2D mTexture;
uniform float mAlpha;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(mNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = ambient + diffuse;

    color = texture(mTexture,mTexCoord);

    color*=vec4(result,mAlpha);
}
