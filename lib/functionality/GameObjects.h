#pragma once

#include "../ustawienia.h"
#include "LTexture.h"
#include "../rendering/Kamera.h"

UST& ust = UST::pobierz_ustawienia();

//Abstract interface for all Game objects
class _GameObject
{
protected:
	int mVisibleX, mVisibleY;

	int mWidth, mHeight;

public:
	int getX() {
		return mVisibleX;
	}
	int getY() {
		return mVisibleY;
	}

	int getWidth() {
		return mWidth;
	}
	int getHeight() {
		return mHeight;
	}
};


// Abstract interface for Drawable objects
class _Drawable
{
protected:
	std::shared_ptr<SDL_Rect> mClip;
	double mAngle;
	std::shared_ptr<SDL_Point> mCenter;
	SDL_RendererFlip mFlip;

	rendererType* mRenderer;
	kameraType mKamera;
	textureType mTexture;
public:
	_Drawable(rendererType& renderer, textureType texture, kameraType kamera = nullptr) : mKamera(kamera), mTexture(texture)
	{
		mRenderer = &renderer;

		mClip = nullptr;
		mAngle = 0;
		mCenter = nullptr;
		mFlip = SDL_FLIP_NONE;
	}

	virtual void render() = 0;
};


// Abstract interface for Updatable objects
class _Updatable
{
public:
	_Updatable() {};

	virtual void update(const int deltaTime) = 0;
	virtual void interpolate(const double alpha) = 0;
};

// Only classes below should be inherited from

// Movable Game object
class Movable : public _GameObject, public _Updatable
{
protected:
	const double VELOCITY = 0;

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

// Movable and drawable Game object
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

};

// _Updatable and _Drawable Game object
class DUGameObject : public DGameObject, public _Updatable
{

};