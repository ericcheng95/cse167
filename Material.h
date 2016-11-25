#pragma once
#include "main.h"
using namespace glm;

struct Material
{
	vec3 diffuseCoeff;
	float shininessExp;
	vec3 specularCoeff;
	vec3 ambientCoeff;
	float reflectivity;
};