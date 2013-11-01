#version 330 core

in vec3 vertexInterpolatedColor;
in vec2 fragTexcoord;

uniform sampler2D colorTexture;

uniform int selected;
uniform vec3 chroma_color;
uniform vec3 chroma_tolerance;
uniform float brightness;
uniform float contrast;
uniform vec3 surface_color;
uniform int lite_render;


out vec4 fragment_color;

void main( void )
{
	if(lite_render != 0)
	{
            fragment_color = vec4(vertexInterpolatedColor, 1.0) + vec4(0.0, 0.0, 0.0, 0.0);//add empty vec4 needed to fix issue on AMD FirePro v3800
            return;
	}
		
        fragment_color = texture2D(colorTexture, fragTexcoord);
	fragment_color.rgb = ((fragment_color .rgb - 0.5f) * max(contrast, 0)) + brightness*0.5f + surface_color*0.5f + vertexInterpolatedColor;
	
	if(selected > 0)
	{
		fragment_color = sqrt(fragment_color);
	}

	if(chroma_color.x > fragment_color.r - chroma_tolerance.x && chroma_color.x < fragment_color.r + chroma_tolerance.x && 
    	chroma_color.y > fragment_color.g - chroma_tolerance.y && chroma_color.y < fragment_color.g + chroma_tolerance.y &&
    	chroma_color.z > fragment_color.b - chroma_tolerance.z && chroma_color.z < fragment_color.b + chroma_tolerance.z)
	{       
		fragment_color.a = 0.0f;
	}
	else
	{
		fragment_color.a = 1.0f;
	}
}
