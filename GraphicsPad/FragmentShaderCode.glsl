#version 430

in vec3 normalWorld;
in vec3 vertexPositionWorld;

uniform vec3 lightPositionWorld;

out vec4 daColor;

void main()
{
    // Diffuse lighting
    vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
    float diffuseLight = dot(lightVectorWorld, normalize(normalWorld));

    daColor = vec4(diffuseLight, diffuseLight, diffuseLight, 1.0);  // varying data
}
