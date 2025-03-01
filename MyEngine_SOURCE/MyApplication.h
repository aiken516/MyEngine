#pragma once
#include "CommonInclude.h"
#include "MyGameObject.h"

namespace Source
{
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND hwnd, UINT width, UINT height);
		void Run();
		void Update();
		void LateUpdate();
		void Render();
	private:
		void ClearRenderTarget();
		void CopyRenderTarget(HDC source, HDC dest);
		void AdjustApplicationWindow(HWND hwnd, UINT width, UINT height);
		void CreateBackBuffer();

		HWND hwnd_;// 윈도우 핸들
		HDC hdc_; // 드로잉 핸들

		HDC backHdc_; // 먼저 그리고 그린 값을 넘겨주는 드로잉 핸들, 더블 버퍼링용
		HBITMAP backBitMap_;// 더블 버퍼링으로 화면을 표출하기 위한 버퍼, 드로잉 핸들에도 1개 있음

		UINT width_;//화면의 해상도 값
		UINT height_;//화면의 해상도 값
	};
}


