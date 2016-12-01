#include "Geode.h"
const vec3 Geode::xAxis = vec3(1, 0, 0);
const vec3 Geode::yAxis = vec3(0, 1, 0);
const vec3 Geode::zAxis = vec3(0, 0, 1);
Material* Geode::defaultMaterial = new Material{
	vec3(0.6f, 0.6f, 0.6f),
	10,
	vec3(0.1f, 0.1f, 0.1f),
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
	findMinMax(vec4(m->minX, m->minY, m->minZ, 1.0f), vec4(m->maxX, m->maxY, m->maxZ, 1.0f));
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
	geode->parents.push_back(this);
	findMinMax(geode->M * geode->minPos, geode->M * geode->maxPos);
}


void Geode::translate(float x, float y, float z)
{
	translate(glm::translate(vec3(x, y, z)));
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

void Geode::findMinMax(vec4 min, vec4 max)
{
	if (min.x < minPos.x)
	{
		minPos.x = min.x;
	}
	else if (max.x > maxPos.x)
	{
		maxPos.x = max.x;
	}
	if (min.y < minPos.y)
	{
		minPos.y = min.y;
	}
	else if (max.y > maxPos.y)
	{
		maxPos.y = max.y;
	}
	if (min.z < minPos.z)
	{
		minPos.z = min.z;
	}
	else if (max.z > maxPos.z)
	{
		maxPos.z = max.z;
	}
	center = maxPos + minPos;
	boundingRadius = distance(maxPos, center);

	for (auto it = parents.begin(); it != parents.end(); it++)
	{
		findMinMax(M * minPos, M * maxPos);
	}
}
