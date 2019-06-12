#version 430

in layout(location=0) vec3 position;    // in is for varying data
in layout(location=1) vec3 vertexColor;

uniform vec3 dominatingColor; // the uniform keyword is for data that does not change, or is uniform
uniform float yFlip;

out vec3 theColor;

void main()
{
   gl_Position = vec4(position, 1.0);
   gl_Position.y = gl_Position.y * yFlip;

//   theColor = vertexColor;  // varying data
   theColor = dominatingColor;  // uniform data
}
