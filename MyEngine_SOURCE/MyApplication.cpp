#include "MyApplication.h"
#include "MyInput.h"
#include "MyTime.h"
#include "MySceneManager.h"
#include "MyResources.h"
#include "MyCollisionManager.h"
#include "MyRenderManager.h"
#include "MyFmod.h"

namespace Source
{
	Application::Application() :
		_hwnd(nullptr),
		_width(0),
		_height(0)
	{
	}

	Application::~Application()
	{
	
	}

	void Application::Initialize(HWND hwnd, UINT width, UINT height)
	{
		InitApplicationWindow(hwnd, width, height);

		Input::Initailize();	
		Time::Initailze();
		Fmod::Initialize();
		CollisionManager::Initialize();
		SceneManager::Initialize();
		RenderManager::Initialize();
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();

		Destroy();
	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();
		CollisionManager::Update();
		SceneManager::Update();
		RenderManager::Update();
	}

	void Application::LateUpdate()
	{
		CollisionManager::LateUpdate();
		SceneManager::LateUpdate();
		RenderManager::LateUpdate();
	}

	void Application::Render()
	{
		_graphicDevice->BeginDraw(D2D1::ColorF(D2D1::ColorF::White, 1.0f));
		
		SceneManager::Render();
		//RenderManager::Render(_graphicDevice->GetRenderTarget());
		RenderManager::ClearRenderRequests();
		SceneManager::OnDrawGizmos();

		_graphicDevice->EndDraw();
	}

	void Application::Destroy()
	{
		SceneManager::Destroy();
	}

	void Application::Release()
	{
		//Static한 클래스, 싱글턴으로 작동하는 클래스를 메모리 해제
		SceneManager::Release();
		Resources::Release();
	}

	void Application::InitApplicationWindow(HWND hwnd, UINT width, UINT height)
	{
		_hwnd = hwnd;

		RECT rect = { 0, 0, width, height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		_width = rect.right - rect.left;
		_height = rect.bottom - rect.top;

		SetWindowPos(_hwnd, nullptr, 0, 0, _width, _height, 0);
		ShowWindow(_hwnd, true);

		_graphicDevice = std::make_unique<Graphics::GraphicDevice>();

		HRESULT hr = _graphicDevice->Initialize(hwnd, width, height);
		if (FAILED(hr))
		{
			MessageBox(nullptr, L"GraphicDevice Initialize Fail.", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
	}
}