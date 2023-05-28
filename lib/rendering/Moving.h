#ifndef MOVING
#define MOVING
#include "../ustawienia.h"

class Moving
{
protected:
	const double VELOCITY;

	int mWIDTH;
	int mHEIGHT;

	double mPosX, mPosY;
	double oldX, oldY;

	double mVelX, mVelY;

	int xPosToRender, yPosToRender;
public:
	Moving(double velocity);

	virtual void move_step(int timeStep_ms);

	virtual void move(double alpha);
};
#endif
