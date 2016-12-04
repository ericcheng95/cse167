#include "main.h"
#include "Geode.h"



/*
*
* ALL MODELS MUST BE CONVEX!!
* Cannot change anything (parent, child, any parent/child transforms, etc.) after doing this.
* must only have 1 parent, and so forth up the tree.
*/


class StaticCollidableGeode
{
public:
	static list<StaticCollidableGeode*> all;
	static void add(Geode* geode);

	//Returns all colliding <face normals><face vertices to draw (moved in direction of normal slightly)>
	//Other geode must have no children (only a model) and must be directly attached to world.
	static vector<vector<GLfloat>*>* collide(Geode* other);
private:

	Geode* geode;
	StaticCollidableGeode(Geode* geode); 

	static void getPossibles(vector<Geode*>* possible, Geode* g, Geode* other);

	static bool within(Geode* g, Geode* other);
	static bool within(vec4 vec, Geode* g);
	static bool withinModel(Geode* g, Geode* other);
	static bool withinModel(vec4 vec, Geode* m);


	static bool faceAndSegmentIntersect(vec3 sa, vec3 sb, vec3 n, vec3 a, vec3 b, vec3 c);
};
