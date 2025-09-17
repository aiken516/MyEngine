#pragma once
#include "CommonInclude.h"
#include "MyGameObject.h"
#include "MyGraphicDevice.h"

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
		
		HWND GetHWND() const { return _hwnd; }
		UINT GetWidth() const { return _width; }
		UINT GetHeight() const { return _height; }

		//������
		Graphics::GraphicDevice* GetGraphicDevice() const { return _graphicDevice.get(); }

	private:
		void InitApplicationWindow(HWND hwnd, UINT width, UINT height);

		HWND _hwnd;// ������ �ڵ�

		UINT _width;//ȭ���� �ػ� ��
		UINT _height;//ȭ���� �ػ� ��

		std::unique_ptr<Graphics::GraphicDevice> _graphicDevice;
	};
}


