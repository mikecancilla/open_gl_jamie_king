#version 430

in vec3 normalWorld;
in vec3 vertexPositionWorld;

uniform vec3 lightPositionWorld;
uniform vec4 ambientLight;

out vec4 daColor;

void main()
{
    // Diffuse lighting
    vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
    float diffuseBrightness = dot(lightVectorWorld, normalize(normalWorld));
    vec4 diffuseLight = vec4(diffuseBrightness, diffuseBrightness, diffuseBrightness, 1.0);  // varying data

    daColor = clamp(diffuseLight, 0, 1) + ambientLight;
}
