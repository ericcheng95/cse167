#include "ActionObject.h"

list<ActionObject*> ActionObject::actionObjects;

ActionObject::ActionObject(bool active = true): active(active)
{
	actionObjects.push_back(this);
}

void ActionObject::activate()
{
	active = true;
}

void ActionObject::deactivate()
{
	active = false;
}

void ActionObject::allPerformActions(float secondsElapsed)
{
	for (auto it = actionObjects.begin(); it != actionObjects.end(); it++)
	{
		(*it)->act(secondsElapsed);
	}
}

void ActionObject::act(float secondsElapsed)
{
}
