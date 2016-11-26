#pragma once
#include "Geode.h"

class Cylinder : public Geode {
public:
	Cylinder() : Geode(new Model("cylinder.obj")) {};
	Cylinder(Material* mat) : Geode(new Model("cylinder.obj"), mat) {};
};
