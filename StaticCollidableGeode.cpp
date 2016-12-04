#include "StaticCollidableGeode.h"

list<StaticCollidableGeode*> StaticCollidableGeode::all;

void StaticCollidableGeode::add(Geode* geode)
{
	all.push_back(new StaticCollidableGeode(geode));
}

vector<vector<GLfloat>*>* StaticCollidableGeode::collide(Geode* other)
{
	vector<Geode*>* possible = new vector<Geode*>();
	for (auto it = all.begin(); it != all.end(); ++it)
	{
		getPossibles(possible, (*it)->geode, other);
	}

	//https://gamedev.stackexchange.com/questions/44500/how-many-and-which-axes-to-use-for-3d-obb-collision-with-sat
	//SAT to determine separation

	//AND/OR

	//To find the planes: intersect segments and faces by projecting onto normal. If any segment has endpoints on both sides, then 
	//check that the intersection point http://www.ambrsoft.com/TrigoCalc/Plan3D/PlaneLineIntersection_.htm is within the triangle.
	//That face and the 2 faces around the segment are colliding.

	for (auto it = possible->begin(); it != possible->end(); ++it) {
		Geode* p = *it;
		//TODO: take p segments/faces and other segments/faces and pairwise check intersect to get all intersecting faces/segments
		//Other face/segments need to be multiplied by M beware (only needed for collide, so only need to do it as many times as collision check)
	}

}



void StaticCollidableGeode::getPossibles(vector<Geode*>* possible, Geode* g, Geode* other)
{
	if (within(g, other))
	{
		if (withinModel(g, other))
		{
			possible->push_back(g);
		}
		for (auto it = g->children.begin(); it != g->children.end(); ++it)
		{
			getPossibles(possible, (*it), other);
		}
	}
}

StaticCollidableGeode::StaticCollidableGeode(Geode* geode):geode(geode)
{
	geode->computeFaceSegments();
}


bool StaticCollidableGeode::within(Geode* g, Geode* other)
{
	return within(other->M * other->minPos, g) || within(other->M * other->maxPos, g);
}

bool StaticCollidableGeode::within(vec4 vec, Geode* g)
{
	vec4 max = g->maxPos;
	vec4 min = g->minPos;
	return vec.x <= max.x && vec.y <= max.y && vec.z <= max.z && vec.x >= min.x && vec.y >= min.y && vec.z >= min.z;
}

bool StaticCollidableGeode::withinModel(Geode* g, Geode* other)
{
	return withinModel(other->M * other->maxPos, g) || withinModel(other->minPos, g);
}

bool StaticCollidableGeode::withinModel(vec4 vec, Geode* m)
{
	return vec.x <= m->modelMaxPos.x && vec.y <= m->modelMaxPos.y && vec.z <= m->modelMaxPos.z && vec.x >= m->modelMinPos.x && vec.y >= m->modelMinPos.y && vec.z >= m->modelMinPos.z;
}

bool StaticCollidableGeode::faceAndSegmentIntersect(vec3 sa, vec3 sb, vec3 n, vec3 a, vec3 b, vec3 c)
{

	//If segment not cross face or at least on face(on both sides of face plane), return false. use origin as the point on face, so no need subtract
	if (dot(n, sa) * dot(n, sb) > 0)
	{
		return false;
	}

	//Intersetion point of line sa, sb and plane a,b,c (a and n) (not necessarily on segement, but that is guaranteed above)
	vec3 sbsa = sb - sa;
	vec3 p = sa + (a - dot(n, sa)) / dot(n, sbsa) * sbsa;

	//Point p is within or on triangle (not necessarily same plane, but that is guaranteed above)
	vec3 ca = c - a,
		ba = b - a,
		cb = c - b,
		pa = p - a;
	return dot(cross(cb, p - b), cross(cb, a - b)) > 0 && dot(cross(ca, pa), cross(ca, ba)) > 0 && dot(cross(ba, pa), cross(ba, ca)) > 0;

	//function SameSide(p1,p2, a,b)
	//    cp1 = CrossProduct(b-a, p1-a)
	//    cp2 = CrossProduct(b-a, p2-a)
	//    if DotProduct(cp1, cp2) >= 0 then return true
	//    else return false
	//
	//function PointInTriangle(p, a,b,c)
	//    if SameSide(p,a, b,c) and SameSide(p,b, a,c)
	//        and SameSide(p,c, a,b) then return true
	//    else return false
}
