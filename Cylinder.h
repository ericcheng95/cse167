#pragma once
#include "Geode.h"

class Cylinder : public Geode {
public:
	Cylinder() : Geode(model()) {};
	Cylinder(Material* mat) : Geode(model(), mat) {};

private:
	static Model* model()
	{
		static Model* model = new Model("cube.obj");
		return model;
	}
};
