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
		static float DeltaTime() { return _deltaTime; };
	private:
		static LARGE_INTEGER _cpuFrequency;
		static LARGE_INTEGER _prevCpuFrequency;
		static LARGE_INTEGER _currentCpuFrequency;
		static float _deltaTime;
	};
}
