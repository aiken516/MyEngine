#include "MyTime.h"

namespace Source
{
	LARGE_INTEGER Time::_cpuFrequency = {};
	LARGE_INTEGER Time::_prevCpuFrequency = {};
	LARGE_INTEGER Time::_currentCpuFrequency = {};
	float Time::_deltaTime = 0.0f;

	void Time::Initailze()
	{
		//CPU�� ���� ������ �޾ƿ���
		QueryPerformanceFrequency(&_cpuFrequency);

		//CPU�� ���α׷� ���� �� ������
		QueryPerformanceCounter(&_prevCpuFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&_currentCpuFrequency);

		float frequencyDifference = static_cast<float>(_currentCpuFrequency.QuadPart - _prevCpuFrequency.QuadPart);

		_deltaTime = frequencyDifference / static_cast<float>(_cpuFrequency.QuadPart);

		_prevCpuFrequency.QuadPart = _currentCpuFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		static float time = 0.0f;

		time += _deltaTime;

		wchar_t str[50] = L"";

		int fps = 1.0f / _deltaTime;

		swprintf_s(str, 50, L"Time : %d", fps);
		int length = wcsnlen_s(str, 50);

		//swprintf_s(str, 50, L"Time : %f", time);
		//int length = wcsnlen_s(str, 50);
		TextOut(hdc, 0, 0, str, length);
	}
}