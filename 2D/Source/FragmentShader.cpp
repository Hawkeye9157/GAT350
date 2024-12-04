#include "FragmentShader.h"

color4_t FragmentShader::Process(const fragment_input_t& fragment)
{
	float average = (fragment.color.r + fragment.color.g + fragment.color.b) / 3.0f;
	return {average,average,average,1};
	//return color4_t{ 1,0,0,1 };
}


