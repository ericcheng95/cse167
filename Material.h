#pragma once
#include "main.h"

struct Material
{
	vec3 diffuseCoeff;
	float shininessExp;
	vec3 specularCoeff;
	vec3 ambientCoeff;
	float reflectivity;
};