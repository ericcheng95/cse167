#pragma once
#include "main.h"
#include "shader.h"
#include "Material.h"
#include "Model.h"



class Geode
{
public:
	static const vec3 xAxis;
	static const vec3 yAxis;
	static const vec3 zAxis;
	static Material* defaultMaterial;
	static int geodeCounter;

	static Geode* scene;
	

	int id;
	Material* material;
	list<Geode*> children;
	list<Geode*> parents;
	mat4 M;
	
	vec4 minPos = vec4(999999.9f, 999999.9f, 999999.9f, 0);
	vec4 maxPos = vec4(-999999.9f, -999999.9f, -999999.9f, 0);
	vec4 center;
	float boundingRadius;

	Geode();
	Geode(Material* mat);
	Geode(Model* m);
	Geode(Model* m, Material* mat);
	Geode(mat4 M);
	Geode(Model* m, Material* mat, mat4 M);

	void draw(mat4 C, unsigned int shader);
	void translate(float x, float y, float z);
	void translate(mat4 T);
	void scale(float amountX, float amountY, float amountZ);
	void rotate(float degreesX, float degreesY, float degreesZ);
	void rotate(mat4 R);
	void reset();
	void set(mat4 m);
	void add(Geode* geode);

private:

	Model* model;
	void findMinMax(vec4 min, vec4 max);
};
