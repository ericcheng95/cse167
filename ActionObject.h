#include "main.h"

class ActionObject
{
public:
	static void allPerformActions(float secondsElapsed); //Runs all active ActionObjects. Called in main

	virtual void act(float secondsElapsed);
	ActionObject(bool active);
	void activate();
	void deactivate();
private:
	static list<ActionObject*> actionObjects;

	bool active;
};

