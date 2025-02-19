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

		void Initialize(HWND hwnd);
		void Run();
		void Update();
		void LateUpdate();
		void Render();
	private:
		HWND mHWND;// 윈도우 핸들
		HDC mHDC; // 드로잉 핸들

		GameObject player;
	};
}


