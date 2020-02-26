#include "Timing.h"
#include "ctime"
#include <Windows.h>


static LARGE_INTEGER StartTime;
static double freqms = 0;

void Engine::Timing::Init()
{
	StartTime.QuadPart = 0;

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	freqms = static_cast<double>(freq.QuadPart / 1000);
}

float Engine::Timing::CalcTimeSinceLastCall()
{
	float	g_LastFrameTime_ms;

	// Grab the CPU tick counter
	LARGE_INTEGER EndTime;
	QueryPerformanceCounter(&EndTime);

	if (StartTime.QuadPart) {
		// How many ticks have elapsed since we last did this
		double elapsedTicks = static_cast<double>(EndTime.QuadPart - StartTime.QuadPart);

		// Calculate the frame time - converting ticks to ms.
		g_LastFrameTime_ms = static_cast<double>(elapsedTicks / freqms);
	}
	else {
		g_LastFrameTime_ms = 13.3f; // Assume a 60Hz frame for first call.
	}
	// Note start of this frame
	StartTime.QuadPart = EndTime.QuadPart;

	return g_LastFrameTime_ms;
}