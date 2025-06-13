#include "MyApplication.h"
#include "MyInput.h"
#include "MyTime.h"
#include "MySceneManager.h"
#include "MyResources.h"
#include "MyCollisionManager.h"
#include "MyFmod.h"

namespace Source
{
	Application::Application() :
		_hwnd(nullptr),
		_hdc(nullptr),
		_width(0),
		_height(0),
		_backHdc(NULL),
		_backBitMap(NULL)
	{

	}

	Application::~Application()
	{
	
	}

	void Application::Initialize(HWND hwnd, UINT width, UINT height)
	{
		AdjustApplicationWindow(hwnd, width, height);
		CreateBackBuffer();

		Input::Initailize();	
		Time::Initailze();
		Fmod::Initialize();
		CollisionManager::Initialize();
		SceneManager::Initialize();
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
	}

	void Application::LateUpdate()
	{
		CollisionManager::LateUpdate();
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
		//TEST 배경색, 추후에 분리
		UINT r = 128;
		UINT g = 128;
		UINT b = 128;
		
		ClearRenderTarget(r, g, b);

		Time::Render(_backHdc);
		CollisionManager::Render(_backHdc);
		SceneManager::Render(_backHdc);

		CopyRenderTarget(_backHdc, _hdc);
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

	void Application::ClearRenderTarget(UINT r, UINT g, UINT b)
	{
		HBRUSH colorBrush = (HBRUSH)CreateSolidBrush(RGB(r, g, b));
		HBRUSH oldBrush = (HBRUSH)SelectObject(_backHdc, colorBrush);

		Rectangle(_backHdc, -1, -1, _width + 1, _height + 1); // 흰 사각형을 전체에 채워 그림

		(HBRUSH)SelectObject(_backHdc, oldBrush);
		DeleteObject(colorBrush);
	}

	void Application::CopyRenderTarget(HDC source, HDC dest)
	{
		BitBlt(dest, 0, 0, _width, _height, source, 0, 0, SRCCOPY);
	}

	void Application::AdjustApplicationWindow(HWND hwnd, UINT width, UINT height)
	{
		_hwnd = hwnd;
		_hdc = GetDC(_hwnd);

		RECT rect = { 0, 0, width, height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		_width = rect.right - rect.left;
		_height = rect.bottom - rect.top;

		SetWindowPos(_hwnd, nullptr, 0, 0, _width, _height, 0);
		ShowWindow(_hwnd, true);
	}

	void Application::CreateBackBuffer()
	{
		//윈도우 해상도에 맞게 백버퍼 생성 (캔버스)
		_backBitMap = CreateCompatibleBitmap(_hdc, _width, _height);
		_backHdc = CreateCompatibleDC(_hdc);

		HBITMAP oldBitMap = (HBITMAP)SelectObject(_backHdc, _backBitMap);
		DeleteObject(oldBitMap);
	}
}