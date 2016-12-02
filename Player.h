#pragma once
#include "main.h"
#include "ActionObject.h"

class Player : public ActionObject
{
public:
	void act(float elapsedSeconds) override;
};
