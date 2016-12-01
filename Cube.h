#pragma once
#include "Geode.h"

class Cube :
	public Geode
{
public:
	Cube() : Geode(model())
	{
	};

	Cube(Material* mat) : Geode(model(), mat)
	{
	};
private:
	static Model* model()
	{
		static Model* model = new Model("cube.obj");
		return model;
	}
};
