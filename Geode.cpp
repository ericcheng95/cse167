#include "Geode.h"
const vec3 Geode::xAxis = vec3(1, 0, 0);
const vec3 Geode::yAxis = vec3(0, 1, 0);
const vec3 Geode::zAxis = vec3(0, 0, 1);
Material* Geode::defaultMaterial = new Material{
	vec3(1.0f, 1.0f, 1.0f),
	10,
	vec3(1.0f, 1.0f, 1.0f),
	vec3(0.2f, 0.2f, 0.2f),
	0.0f };

int Geode::geodeCounter = 1;
Geode* Geode::scene = new Geode();

void Geode::draw(mat4 C, unsigned int shaderProgram)
{
	mat4 CM = C * M;
	if (model != nullptr) {
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &CM[0][0]);
		glUniform3fv(glGetUniformLocation(shaderProgram, "material.diffuseCoeff"), 1, &material->diffuseCoeff[0]);
		glUniform3fv(glGetUniformLocation(shaderProgram, "material.specularCoeff"), 1, &material->specularCoeff[0]);
		glUniform3fv(glGetUniformLocation(shaderProgram, "material.ambientCoeff"), 1, &material->ambientCoeff[0]);
		glUniform1f(glGetUniformLocation(shaderProgram, "material.shininessExp"), material->shininessExp);
		glUniform1f(glGetUniformLocation(shaderProgram, "material.reflectivity"), material->reflectivity);
		model->draw();
	}

	for (auto it = children.begin(); it != children.end(); it++)
	{
		(*it)->draw(CM, shaderProgram);
	}
}


Geode::Geode(Model* m, Material* mat, mat4 M) : model(m), material(mat), M(M)
{
	id = geodeCounter++;
}

Geode::Geode(): Geode(nullptr, defaultMaterial, mat4(1.0f))
{
}

Geode::Geode(Material* mat): Geode(nullptr, material, mat4(1.0f))
{
}

Geode::Geode(Model* m): Geode(m, defaultMaterial)
{
}

Geode::Geode(Model* m, Material* mat):
	Geode(m, mat, mat4(1.0f))
{
}

Geode::Geode(mat4 M):
	Geode(nullptr, defaultMaterial, M)
{
}

void Geode::reset()
{
	M = mat4(1.0f);
}

void Geode::set(mat4 m)
{
	M = m;
}

void Geode::add(Geode* geode)
{
	children.push_back(geode);
}

void Geode::remove(Geode* geode)
{
	children.remove(geode);
}

void Geode::translate(float x, float y, float z)
{
	M = glm::translate(vec3(x, y, z)) * M;
}

void Geode::translate(mat4 T)
{
	M = T * M;
}

void Geode::scale(float amountX, float amountY, float amountZ)
{
	M = glm::scale(vec3(amountX, amountY, amountZ)) * M;
}

void Geode::rotate(float radiansX, float radiansY, float radiansZ)
{
	M = glm::rotate(radiansX, xAxis) * glm::rotate(radiansY, yAxis) * glm::rotate(radiansZ, zAxis) * M;
}

void Geode::rotate(mat4 R)
{
	M = R * M;
}
