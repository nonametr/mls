#version 330 core

in vec3 vertexInterpolatedColor;
in vec2 fragTexcoord;

uniform sampler2D colorTexture;
uniform int render_type;

out vec4 fragment_color;

void main( void )
{
    if(render_type == 0)//normal render
    {
        fragment_color = texture2D(colorTexture, fragTexcoord);
 	fragment_color.rgb += vertexInterpolatedColor;
        return;
    }
    else if(render_type == 1)//render YUV
    {
        fragment_color = texture2D(colorTexture, fragTexcoord);
        fragment_color.rgb += vertexInterpolatedColor;

        fragment_color.r = fragment_color.r * 0.299 + fragment_color.g * 0.587 + fragment_color.b * 0.114;
        fragment_color.g = fragment_color.r * -0.169 + fragment_color.g * -0.332 + fragment_color.b * 0.500 + 128.0;
        fragment_color.b = fragment_color.r * 0.500 + fragment_color.g * -0.419 + fragment_color.b * -0.0813 + 128.0;
    }
}
