#version 330 core

in vec3 fragPos;
in vec3 mNormal;
in vec2 mTexCoord;
out vec4 color;
uniform sampler2D mTexture;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(mNormal);
    vec3 lightDir = lightPos - fragPos;
    float distan=length(lightDir);
    lightDir=normalize(lightDir);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    float attenuation=1+0.0007*distan+0.00002*distan*distan;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = 0.5 * spec * lightColor;
    vec3 result = ambient + diffuse+specular;

    color = texture(mTexture,mTexCoord)*vec4(result/attenuation*2,1.0);
}
