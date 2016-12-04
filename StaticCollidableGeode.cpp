#include "StaticCollidableGeode.h"

list<StaticCollidableGeode*> StaticCollidableGeode::all;

void StaticCollidableGeode::add(Geode* geode)
{
	all.push_back(new StaticCollidableGeode(geode));
}

vector<Face*>* StaticCollidableGeode::collide(Geode* other)
{
	vector<Geode*>* possible = new vector<Geode*>();
	for (auto it = all.begin(); it != all.end(); ++it)
	{
		getPossibles(possible, (*it)->geode, other);
	}

	//	//https://gamedev.stackexchange.com/questions/44500/how-many-and-which-axes-to-use-for-3d-obb-collision-with-sat
	//	//SAT to determine separation
	//To find the planes my thoughts: intersect segments and faces by projecting onto normal. If any segment has endpoints on both sides, then 
	//check that the intersection point http://www.ambrsoft.com/TrigoCalc/Plan3D/PlaneLineIntersection_.htm is within the triangle.
	//That face and the 2 faces around the segment are colliding.

	vector<Face*>* intersecting = new vector<Face*>();
	mat4& CM = other->M; //Other is directly attached to world
	for (auto it = possible->begin(); it != possible->end(); ++it)
	{
		Geode* p = *it;
		for (auto f = p->faces->begin(); f != p->faces->end(); ++f)
		{
			Face* face = *f;
			for (auto s = other->segments->begin(); s != other->segments->end(); ++s)
			{
				Segment* segment = transformSegment(*s, CM);
				if (faceAndSegmentIntersect(face, segment))
				{
					intersecting->push_back(face);
					Face* f1 = (*other->faces)[segment->f1];
					if (f1 != nullptr)
					{
						intersecting->push_back(transformFace(f1, CM));
					}
					Face* f2 = (*other->faces)[segment->f2];
					if (f2 != nullptr)
					{
						intersecting->push_back(transformFace(f2, CM));
					}
				}
			}
		}
		for (auto f = other->faces->begin(); f != other->faces->end(); ++f)
		{
			Face* face = transformFace(*f, CM);
			for (auto s = p->segments->begin(); s != p->segments->end(); ++s)
			{
				Segment* segment = *s;
				if (faceAndSegmentIntersect(face, segment))
				{
					intersecting->push_back(face);
					Face* f1 = (*p->faces)[segment->f1];
					if (f1 != nullptr)
					{
						intersecting->push_back(f1);
					}
					Face* f2 = (*p->faces)[segment->f2];
					if (f2 != nullptr)
					{
						intersecting->push_back(f2);
					}
				}
			}
		}
	}
	return intersecting;
}


Segment* StaticCollidableGeode::transformSegment(Segment* segment, mat4& CM)
{
	return new Segment{
		vec3(CM * vec4(segment->a, 1.0f)),
		vec3(CM * vec4(segment->b, 1.0f)),
		segment->f1,
		segment->f2
	};
}

Face* StaticCollidableGeode::transformFace(Face* face, mat4& CM)
{
	return new Face{
		vec3(CM * vec4(face->a, 1.0f)),
		vec3(CM * vec4(face->b, 1.0f)),
		vec3(CM * vec4(face->c, 1.0f)),
		vec3(CM * vec4(face->normal, 1.0f))
	};
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

StaticCollidableGeode::StaticCollidableGeode(Geode* geode): geode(geode)
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

bool StaticCollidableGeode::faceAndSegmentIntersect(Face* face, Segment* segment)
{
	vec3 sa = segment->a;
	vec3 sb = segment->b;
	vec3 n = face->normal;
	vec3 a = face->a;
	vec3 b = face->b;
	vec3 c = face->c;
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
