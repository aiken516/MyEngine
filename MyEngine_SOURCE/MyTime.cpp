#include "MyTime.h"

namespace Source
{
	LARGE_INTEGER Time::cpuFrequency = {};
	LARGE_INTEGER Time::prevCpuFrequency = {};
	LARGE_INTEGER Time::currentCpuFrequency = {};
	float Time::deltaTime = 0.0f;

	void Time::Initailze()
	{
		//CPU의 고유 진동수 받아오기
		QueryPerformanceFrequency(&cpuFrequency);

		//CPU의 프로그램 시작 시 진동수
		QueryPerformanceCounter(&prevCpuFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&currentCpuFrequency);

		float frequencyDifference = static_cast<float>(currentCpuFrequency.QuadPart - prevCpuFrequency.QuadPart);

		deltaTime = frequencyDifference / static_cast<float>(cpuFrequency.QuadPart);

		prevCpuFrequency.QuadPart = currentCpuFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		static float time = 0.0f;

		time += deltaTime;

		wchar_t str[50] = L"";

		int fps = 1.0f / deltaTime;

		swprintf_s(str, 50, L"Time : %d", fps);
		int length = wcsnlen_s(str, 50);

		//swprintf_s(str, 50, L"Time : %f", time);
		//int length = wcsnlen_s(str, 50);
		TextOut(hdc, 0, 0, str, length);
	}
}