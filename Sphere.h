#pragma once
#include "Geode.h"
class Sphere :
	public Geode
{
public:
	Sphere();
	Sphere(Material* mat);
	static Model* generateSphere(int horizontalSegments, int verticalSegments);
};


