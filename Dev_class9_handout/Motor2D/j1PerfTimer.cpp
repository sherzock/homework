// ----------------------------------------------------
// j1PerfTimer.cpp
// Slow timer with microsecond precision
// ----------------------------------------------------

#include "j1PerfTimer.h"
#include "SDL\include\SDL_timer.h"

uint64 j1PerfTimer::frequency = 0;

// ---------------------------------------------
j1PerfTimer::j1PerfTimer()
{
	// TODO 2: Fill Constructor, Start(),ReadMs() and ReadTicks() methods
	// they are simple, one line each!

	Start();
}

// ---------------------------------------------
void j1PerfTimer::Start()
{
	started_at = ReadMs();
	frequency = ReadTicks();
}

// ---------------------------------------------
double j1PerfTimer::ReadMs() const
{
	return SDL_GetPerformanceCounter();
}

// ---------------------------------------------
uint64 j1PerfTimer::ReadTicks() const
{
	SDL_GetPerformanceCounter() - started_at / SDL_GetPerformanceFrequency();
	return 0;
}


