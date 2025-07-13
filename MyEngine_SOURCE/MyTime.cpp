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

	void Time::Render()
	{

	}
}