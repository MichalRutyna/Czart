#pragma once

#include "../ustawienia.h"
#include "LTexture.h"
#include "GOInterfaces.h"
#include "../rendering/Kamera.h"

static UST& ust = UST::pobierz_ustawienia();

// Movable Game object
class Movable : public _GameObject, public _Updatable
{
protected:
	const double VELOCITY = 1;

	double mVelX = 0, mVelY = 0;

	double mInternalX = 0, mInternalY = 0;
	double mInPreviousX = 0, mInPreviousY = 0;

public:
	Movable() {};
	virtual void update(const int deltaTime);

	virtual void interpolate(const double alpha);

	virtual void move_step(const int timeStep_ms);

	virtual void move(const double alpha);

	virtual void handleCollisions();
};

// Movable and drawable Game object, most object belong to this subclass
class DMovable : public Movable, public _Drawable
{
public:
	DMovable(rendererType& renderer, textureType texture, kameraType kamera = nullptr) : _Drawable(renderer, texture, kamera) {};

	virtual void render();
};


// Update-only Game object
class UGameObject : public _GameObject, public _Updatable
{
public:
	virtual void update(int timeStep_ms) = 0;
	virtual void interpolate(const double alpha) = 0;

};

// Draw-only Game object
class DGameObject : public _GameObject, public _Drawable
{
public:
	DGameObject(rendererType& renderer, textureType texture, kameraType kamera = nullptr) : _Drawable(renderer, texture, kamera) {};

	virtual void render();
};

// Updatable and Drawable Game object
class DUGameObject : public DGameObject, public _Updatable
{

};