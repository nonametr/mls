#version 330 core

in vec3 vertex_color;
in vec3 vertex_position;
in vec2 tex_cords;

out vec3 vertexInterpolatedColor;
out vec2 fragTexcoord;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

void main( void )
{
   	gl_Position   = projectionMatrix * modelViewMatrix * vec4(vertex_position, 1.0);
    	vertexInterpolatedColor = vertex_color;
    
    	fragTexcoord = tex_cords;

}