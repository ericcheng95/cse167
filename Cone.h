#pragma once
#include "Geode.h"

class Cone : public Geode {
public:
	Cone() : Geode(new Model("cone.obj")) {};
	Cone(Material* mat) : Geode(new Model("cone.obj"), mat) {};
};
