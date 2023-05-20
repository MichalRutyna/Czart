#include "../lib/LTimer.h"

LTimer::LTimer()
{
	mStartTicks = 0;
	mPausedTicks = 0;

	mStarted = false;
	mPaused = false;
}

void LTimer::start()
{
	mStarted = true;

	mPaused = false;

	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void LTimer::stop()
{
	mStarted = false;

	mPaused = false;

	mStartTicks = 0;
	mPausedTicks = 0;
}

void LTimer::pause()
{
	if (mStarted && !mPaused)
	{
		mPaused = true;

		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void LTimer::unpause()
{
	if(mStarted && mPaused)
	{
		mPaused = false;

		mStartTicks = SDL_GetTicks() - mPausedTicks;
		mPausedTicks = 0;
	}
}

uint32_t LTimer::getTicks()
{
	uint32_t time = 0;

	if (mStarted)
	{
		if (!mPaused)
		{
			// zwróć aktualny czas - czas kiedy rozpoczęto
			time = SDL_GetTicks() - mStartTicks;
		}
		else
		{
			// zwróć czas kiedy zatrzymano
			time = mPausedTicks;
		}
	}
	return time;
}

bool LTimer::isStarted()
{
	return mStarted;
}

bool LTimer::isPaused()
{
	return mPaused;
}