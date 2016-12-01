#pragma once
#include "Geode.h"

class Pyramid : public Geode {
public:
	Pyramid() : Geode(model()) {};
	Pyramid(Material* mat) : Geode(model(), mat) {};
private:
	static Model* model()
	{
		static Model* model = new Model("pyramid.obj");
		return model;
	}
};

