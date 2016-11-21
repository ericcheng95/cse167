#pragma once
#include "Node.h"
#include <list>

class Group : public Node
{
public:
	list<Node*> children;
	Group();
	~Group();
	void addChild(Node* node);
	void removeChild(Node* node);
	void draw(mat4 C) override;
};
