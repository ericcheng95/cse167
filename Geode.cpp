#include "Geode.h"
#include "PrimaryWindow.h"
#include "camera.h"
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

int Geode::uModel, Geode::uDiffuse, Geode::uSpecular, Geode::uAmbient, Geode::uShininess, Geode::uReflectivity;

void Geode::draw(mat4 C, unsigned int shaderProgram)
{
	mat4 CM = C * M;
	// Cull if out of bounds
	if (PrimaryWindow::enableCulling && enableCulling) {
		vec3 v = vec3(CM * center);
		if (dot((v - Camera::cameraFrustumPointLeft), Camera::cameraFrustumNormalLeft) > boundingRadius
			|| dot((v - Camera::cameraFrustumPointRight), Camera::cameraFrustumNormalRight) > boundingRadius
			|| dot((v - Camera::cameraFrustumPointTop), Camera::cameraFrustumNormalTop) > boundingRadius
			|| dot((v - Camera::cameraFrustumPointBottom), Camera::cameraFrustumNormalBottom) > boundingRadius
			|| dot((v - Camera::cameraFrustumPointNear), Camera::cameraFrustumNormalNear) > boundingRadius
			|| dot((v - Camera::cameraFrustumPointFar), Camera::cameraFrustumNormalFar) > boundingRadius)
		{
			return;
		}
	}

	if (model != nullptr) {
		glUniformMatrix4fv(uModel, 1, GL_FALSE, &CM[0][0]);
		glUniform3fv(uDiffuse, 1, &material->diffuseCoeff[0]);
		glUniform3fv(uSpecular, 1, &material->specularCoeff[0]);
		glUniform3fv(uAmbient, 1, &material->ambientCoeff[0]);
		glUniform1f(uShininess, material->shininessExp);
		glUniform1f(uReflectivity, material->reflectivity);
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
	if (m != nullptr) {
		findMinMax(vec4(m->minX, m->minY, m->minZ, 1.0f), vec4(m->maxX, m->maxY, m->maxZ, 1.0f));
	}
}

void Geode::init(unsigned int shader)
{
	scene->enableCulling = false;
	Geode::uModel = glGetUniformLocation(shader, "model");
	Geode::uDiffuse = glGetUniformLocation(shader, "material.diffuseCoeff");
	Geode::uSpecular = glGetUniformLocation(shader, "material.specularCoeff");
	Geode::uAmbient = glGetUniformLocation(shader, "material.ambientCoeff");
	Geode::uShininess = glGetUniformLocation(shader, "material.shininessExp");
	Geode::uReflectivity = glGetUniformLocation(shader, "material.reflectivity");
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
	findParentMinMax();
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

void Geode::translate(vec3 t)
{
	translate(glm::translate(t));
}

void Geode::translate(mat4 T)
{
	M = T * M;
	findParentMinMax();
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
	if (enableCulling) {
		if (min.x < minPos.x)
		{
			minPos.x = min.x;
		}
		if (max.x > maxPos.x)
		{
			maxPos.x = max.x;
		}
		if (min.y < minPos.y)
		{
			minPos.y = min.y;
		}
		if (max.y > maxPos.y)
		{
			maxPos.y = max.y;
		}
		if (min.z < minPos.z)
		{
			minPos.z = min.z;
		}
		if (max.z > maxPos.z)
		{
			maxPos.z = max.z;
		}
		center = maxPos + minPos;
		boundingRadius = distance(maxPos, center) + 3.0f;

		for (auto it = parents.begin(); it != parents.end(); it++)
		{
			findMinMax(M * minPos, M * maxPos);
		}
	}
}

void Geode::findParentMinMax()
{
	for (auto it = parents.begin(); it != parents.end(); it++)
	{
		findMinMax(M * minPos, M * maxPos);
	}
}
