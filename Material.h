#pragma once
#include "main.h"
using namespace glm;

struct Material
{
	vec3 diffuseCoeff;
	float specularExp;
	vec3 ambientCoeff;
	float reflectivity;
};

