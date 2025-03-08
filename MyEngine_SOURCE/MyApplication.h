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

		HWND _hwnd;// ������ �ڵ�
		HDC _hdc; // ����� �ڵ�

		HDC _backHdc; // ���� �׸��� �׸� ���� �Ѱ��ִ� ����� �ڵ�, ���� ���۸���
		HBITMAP _backBitMap;// ���� ���۸����� ȭ���� ǥ���ϱ� ���� ����, ����� �ڵ鿡�� 1�� ����

		UINT _width;//ȭ���� �ػ� ��
		UINT _height;//ȭ���� �ػ� ��
	};
}


