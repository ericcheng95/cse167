#pragma once
#include "main.h"

struct DirectionalLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float attenuation;
};


struct SpotLight
{
	vec3 direction;
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float attenuation;
	float spotCutoff;
	float spotExponent;
};

class Light
{
public:
	static vector<DirectionalLight> directionalLights;
	static vector<PointLight> pointLights;
	static vector<SpotLight> spotLights;
	static void drawLights(unsigned int shader);

};

