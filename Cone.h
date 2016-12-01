#pragma once
#include "Geode.h"

class Cone : public Geode {
public:
	Cone() : Geode(model()) {};
	Cone(Material* mat) : Geode(model(), mat) {};
private:
	static Model* model()
	{
		static Model* model = new Model("cone.obj");
		return model;
	}
};
