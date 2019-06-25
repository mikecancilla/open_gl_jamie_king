#version 430

in vec3 normalWorld;
in vec3 vertexPositionWorld;

uniform vec3 lightPositionWorld;
uniform vec3 eyePositionWorld;
uniform vec4 ambientLight;

out vec4 daColor;

void main()
{
    // Diffuse lighting
    vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
    float diffuseBrightness = dot(lightVectorWorld, normalize(normalWorld));
    vec4 diffuseLight = vec4(diffuseBrightness, diffuseBrightness, diffuseBrightness, 1.0);  // varying data

    // Specular lighting
    vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, normalWorld);
    vec3 eyeVectorWorld = normalize(eyePositionWorld - vertexPositionWorld);
    float s = dot(reflectedLightVectorWorld, eyeVectorWorld);
    vec4 specularLight = vec4(s, s, s, 1);

    daColor = ambientLight + clamp(diffuseLight, 0, 1) + clamp(specularLight, 0, 1);
}
