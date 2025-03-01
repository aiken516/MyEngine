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

		HWND hwnd_;// ������ �ڵ�
		HDC hdc_; // ����� �ڵ�

		HDC backHdc_; // ���� �׸��� �׸� ���� �Ѱ��ִ� ����� �ڵ�, ���� ���۸���
		HBITMAP backBitMap_;// ���� ���۸����� ȭ���� ǥ���ϱ� ���� ����, ����� �ڵ鿡�� 1�� ����

		UINT width_;//ȭ���� �ػ� ��
		UINT height_;//ȭ���� �ػ� ��
	};
}


