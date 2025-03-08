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
		
		HDC GetHDC() { return _hdc; }

	private:
		void ClearRenderTarget();
		void CopyRenderTarget(HDC source, HDC dest);
		void AdjustApplicationWindow(HWND hwnd, UINT width, UINT height);
		void CreateBackBuffer();

		HWND _hwnd;// 윈도우 핸들
		HDC _hdc; // 드로잉 핸들

		HDC _backHdc; // 먼저 그리고 그린 값을 넘겨주는 드로잉 핸들, 더블 버퍼링용
		HBITMAP _backBitMap;// 더블 버퍼링으로 화면을 표출하기 위한 버퍼, 드로잉 핸들에도 1개 있음

		UINT _width;//화면의 해상도 값
		UINT _height;//화면의 해상도 값
	};
}


