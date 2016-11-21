#include "Group.h"

using namespace std;

Group::Group()
{
}


Group::~Group()
{

}

void Group::draw(mat4 C)
{
	for (auto it = children.begin(); it != children.end(); it++)
	{
		(*it)->draw(C);
	}
}

void Group::addChild(Node* node)
{
	children.push_back(node);
}

void Group::removeChild(Node* node)
{
	children.remove(node);
}
