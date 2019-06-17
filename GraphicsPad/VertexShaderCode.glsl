#version 430

in layout(location=0) vec3 position;    // in is for varying data
in layout(location=1) vec3 vertexColor;
in layout(location=2) mat4 fullTransformMatrix;

//uniform vec3 dominatingColor; // the uniform keyword is for data that does not change, or is uniform
//uniform float yFlip;

//uniform mat4 modelTransformMatrix;
//uniform mat4 fullTransformMatrix;

out vec3 theColor;

void main()
{
   //gl_Position = vec4(position, 1.0);

   vec4 v = vec4(position, 1.0);
   //vec4 newPosition = modelTransformMatrix * v;
   //vec4 projectedPosition = projectionMatrix * newPosition;
   //gl_Position = projectedPosition;
   gl_Position = fullTransformMatrix * v;

//   gl_Position.y = gl_Position.y * yFlip;

   theColor = vertexColor;  // varying data
//   theColor = dominatingColor;  // uniform data
}
