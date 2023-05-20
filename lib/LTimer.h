#ifndef LTIMER
#define LTIMER

#include <cstdint>
#include <SDL.h>

class LTimer
{
public:
	LTimer();

	void start();
	void stop();
	void pause();
	void unpause();

	uint32_t getTicks();

	bool isStarted();
	bool isPaused();

private:
	// snapshot z wystartowania
	uint32_t mStartTicks;

	// snapshot z zapauzowania
	uint32_t mPausedTicks;

	bool mPaused;
	bool mStarted;
};

#endif