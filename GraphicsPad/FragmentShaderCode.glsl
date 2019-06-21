#version 430

in vec3 theNormal;
in vec3 thePosition;

uniform vec3 lightPosition;

out vec4 daColor;

void main()
{
    // Diffuse lighting
    vec3 lightVector = normalize(lightPosition - thePosition);
    float diffuseLight = dot(lightVector, theNormal);

    daColor = vec4(diffuseLight, diffuseLight, diffuseLight, 1.0);  // varying data
}
