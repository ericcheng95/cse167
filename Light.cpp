#include "Light.h"

vector<DirectionalLight> Light::directionalLights;
vector<PointLight> Light::pointLights;
vector<SpotLight> Light::spotLights;


void Light::drawLights(unsigned int shader)
{
	glUniform3fv(glGetUniformLocation(shader, "directionalLight.direction"), 1, &directionalLights[0].direction[0]);
	glUniform3fv(glGetUniformLocation(shader, "directionalLight.ambient"), 1, &directionalLights[0].ambient[0]);
	glUniform3fv(glGetUniformLocation(shader, "directionalLight.diffuse"), 1, &directionalLights[0].diffuse[0]);
	glUniform3fv(glGetUniformLocation(shader, "directionalLight.specular"), 1, &directionalLights[0].specular[0]);
	//	glUniform3fv(glGetUniformLocation(shader, "pointLight.position"), 1, &Window::pointLight.position[0]);
	//	glUniform3fv(glGetUniformLocation(shader, "pointLight.ambient"), 1, &Window::pointLight.ambient[0]);
	//	glUniform3fv(glGetUniformLocation(shader, "pointLight.diffuse"), 1, &Window::pointLight.diffuse[0]);
	//	glUniform3fv(glGetUniformLocation(shader, "pointLight.specular"), 1, &Window::pointLight.specular[0]);
	//	glUniform1f(glGetUniformLocation(shader, "pointLight.attenuation"), Window::pointLight.attenuation);
	//
	//
	//	glUniform3fv(glGetUniformLocation(shader, "spotLight.direction"), 1, &Window::spotLight.direction[0]);
	//	glUniform3fv(glGetUniformLocation(shader, "spotLight.position"), 1, &Window::spotLight.position[0]);
	//	glUniform3fv(glGetUniformLocation(shader, "spotLight.ambient"), 1, &Window::spotLight.ambient[0]);
	//	glUniform3fv(glGetUniformLocation(shader, "spotLight.diffuse"), 1, &Window::spotLight.diffuse[0]);
	//	glUniform3fv(glGetUniformLocation(shader, "spotLight.specular"), 1, &Window::spotLight.specular[0]);
	//	glUniform1f(glGetUniformLocation(shader, "spotLight.attenuation"), Window::spotLight.attenuation);
	//	glUniform1f(glGetUniformLocation(shader, "spotLight.spotCutoff"), Window::spotLight.spotCutoff);
	//	glUniform1f(glGetUniformLocation(shader, "spotLight.spotExponent"), Window::spotLight.spotExponent);

}