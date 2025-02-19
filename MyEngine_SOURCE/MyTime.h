#pragma once
#include "CommonInclude.h"

namespace Source
{
	class Time
	{
	public:
		static void Initailze();
		static void Update();
		static void Render(HDC hdc);
		static float DeltaTime() { return deltaTime; };
	private:
		static LARGE_INTEGER cpuFrequency;
		static LARGE_INTEGER prevCpuFrequency;
		static LARGE_INTEGER currentCpuFrequency;
		static float deltaTime;
	};
}
