#pragma once

//Abstract interface for all Game objects
class _GameObject
{
protected:
	int mVisibleX = 0, mVisibleY = 0;

	int mWidth = 0, mHeight = 0;

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