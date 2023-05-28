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

	uint64_t getTicks();

	bool isStarted();
	bool isPaused();

private:
	// snapshot z wystartowania
	uint64_t mStartTicks;

	// snapshot z zapauzowania
	uint64_t mPausedTicks;

	bool mPaused;
	bool mStarted;
};

#endif