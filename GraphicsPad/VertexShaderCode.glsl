#version 430

in layout(location=0) vec3 position;    // in is for varying data
in layout(location=1) vec3 vertexColor;
in layout(location=2) vec3 normal; // Use this to send over data via instance data
//in layout(location=2) mat4 fullTransformMatrix; // Use this to send over data via instance data

//uniform vec3 dominatingColor; // the uniform keyword is for data that does not change, or is uniform
//uniform float yFlip;

uniform vec3 ambientLight;
uniform mat4 fullTransformMatrix; // Use this to send over data via a uniform
uniform mat4 modelToWorldTransformMatrix;

//out vec3 theColor;
out vec3 theNormal;
out vec3 thePosition;

void main()
{
    //gl_Position = vec4(position, 1.0);

    vec4 v = vec4(position, 1.0);
    //vec4 newPosition = modelTransformMatrix * v;
    //vec4 projectedPosition = projectionMatrix * newPosition;
    //gl_Position = projectedPosition;
    gl_Position = fullTransformMatrix * v;

//    gl_Position.y = gl_Position.y * yFlip;

    // Diffuse lighting
//    vec3 lightVector = normalize(lightPosition - position);
//    float diffuseLight = dot(lightVector, normal);

    // Output Color
//    theColor = vec3(gl_Position);
//    theColor = position;
//    theColor = normal;
//    theColor = vec3(diffuseLight, diffuseLight, diffuseLight);  // varying data
//    theColor = vertexColor * ambientLight * diffuseLight;  // varying data
//    theColor = dominatingColor;  // uniform data

//    theNormal = normal;
    // DO NOT TRANSLATE THE NORMAL, just rotate it.
    // Set the 4th parameter to 0 cancel out the translation value
    // If we were to scale our model, then we would have to re-normalize
    // If we did a non-uniform scale, well, there would be more to do
    theNormal = vec3(modelToWorldTransformMatrix * vec4(normal, 0));
//    thePosition = position;
    thePosition = vec3(modelToWorldTransformMatrix * v);
}
