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
	double previousX, previousY;

	double mVelX, mVelY;

	int visibleX, visibleY;
public:
	Moving(double velocity);

	virtual void move_step(int timeStep_ms);

	virtual void move(double alpha);
};
#endif
