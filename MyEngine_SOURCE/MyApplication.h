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
		HWND mHWND;// ������ �ڵ�
		HDC mHDC; // ����� �ڵ�

		GameObject player;
	};
}


