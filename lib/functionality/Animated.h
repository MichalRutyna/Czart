#pragma once

#include <SDL.h>
#include <memory>
#include <vector>
#include "GameObjects.h"
#include "../ustawienia.h"

class Animated
{
protected:
	static const int CLIPS_SIZE = 30;
	std::vector<std::shared_ptr<SDL_Rect>> clips;

	int mFrame = 0;

protected:
	int mCLIP_WIDTH;
	int mCLIP_HEIGHT;

public:
	Animated(int clipW, int clipH);
	void clipUpdate();

};

