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
		void Destroy();

		void Release();
		
		HWND GetHWND() { return _hwnd; }
		HDC GetHDC() { return _hdc; }
		UINT GetWidth() { return _width; }
		UINT GetHeight() { return _height; }

	private:
		void ClearRenderTarget(UINT r = 255, UINT g = 255, UINT b = 255);
		void CopyRenderTarget(HDC source, HDC dest);
		void AdjustApplicationWindow(HWND hwnd, UINT width, UINT height);
		void CreateBackBuffer();

		HWND _hwnd;// ������ �ڵ�
		HDC _hdc; // ����� �ڵ�

		HDC _backHdc; // ���� �׸��� �׸� ���� �Ѱ��ִ� ����� �ڵ�, ���� ���۸���
		HBITMAP _backBitMap;// ���� ���۸����� ȭ���� ǥ���ϱ� ���� ����, ����� �ڵ鿡�� 1�� ����

		UINT _width;//ȭ���� �ػ� ��
		UINT _height;//ȭ���� �ػ� ��
	};
}


