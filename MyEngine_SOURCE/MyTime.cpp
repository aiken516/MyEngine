#include "MyTime.h"

#include "MyRenderManager.h"
#include "MyApplication.h"

extern Source::Application application;

namespace Source
{
	LARGE_INTEGER Time::_cpuFrequency = {};
	LARGE_INTEGER Time::_prevCpuFrequency = {};
	LARGE_INTEGER Time::_currentCpuFrequency = {};
	float Time::_deltaTime = 0.0f;

	void Time::Initailze()
	{
		//CPU의 고유 진동수 받아오기
		QueryPerformanceFrequency(&_cpuFrequency);

		//CPU의 프로그램 시작 시 진동수
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
		static float time = 0.0f;

		time += _deltaTime;

		wchar_t str[50] = L"";

		int fps = 1.0f / _deltaTime;

		swprintf_s(str, 50, L"Time : %d", fps);

		D2D1_MATRIX_3X2_F translationMatrix = D2D1::Matrix3x2F::Translation(0, 0);
		D2D1_MATRIX_3X2_F rotationMatrix = D2D1::Matrix3x2F::Rotation(0);
		D2D1_MATRIX_3X2_F scaleMatrix = D2D1::Matrix3x2F::Scale(1, 1);
		D2D1_MATRIX_3X2_F worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;

		IDWriteFactory* dwriteFactory = application.GetGraphicDevice()->GetDWriteFactory();
		IDWriteTextFormat* myTextFormat = nullptr;

		// 폰트 포맷 생성
		dwriteFactory->CreateTextFormat(
			L"Arial",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			24.0f,
			L"ko-KR",
			&myTextFormat
		);

		TextRequest request{};
		request.text = str;
		request.textRect = D2D1::RectF(0.0f, 0.0f, 200.0f, 50.0f);
		request.color = D2D1::ColorF(D2D1::ColorF::Black);
		request.textFormat = myTextFormat; // 미리 생성된 포맷
		request.transformMatrix = worldMatrix; // 월드 행렬을 넘깁니다.

		RenderManager::AddTextRequest(request);
	}
}