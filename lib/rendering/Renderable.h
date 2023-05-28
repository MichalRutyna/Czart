#ifndef RENDERABLE
#define RENDERABLE

#include "../functionality/LTexture.h"
#include "../ustawienia.h"
#include "../rendering/Kamera.h"
#include <memory>

class Renderable
{
private:
	std::shared_ptr<SDL_Rect> mClip;
	double mAngle;
	std::shared_ptr<SDL_Point> mCenter;
	SDL_RendererFlip mFlip;
	int renderX;
	int renderY;

protected:
	rendererType* mRenderer;
	kameraType mKamera;
	textureType mTexture;


public:
	Renderable(rendererType&, textureType, kameraType = nullptr);

	virtual void render(int posX, int posY); // Pozycje absolutne, kamera odejmowana w funkcji

	void change_clip(int x, int y, int w, int h);
	void change_angle(double angle);
	void change_center(int x, int y);
	void change_flip(TextureFlip);

	int getPosX();
	int getPosY();
	int width();
	int height();
};

#endif // !RENDERABLE
