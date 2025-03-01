#include "MyApplication.h"
#include "MyInput.h"
#include "MyTime.h"
#include "MySceneManager.h"

namespace Source
{
	Application::Application() :
		hwnd_(nullptr),
		hdc_(nullptr),
		width_(0),
		height_(0),
		backHdc_(NULL),
		backBitMap_(NULL)
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
		SceneManager::Initialize();
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
		ClearRenderTarget();

		Time::Render(backHdc_);
		SceneManager::Render(backHdc_);

		CopyRenderTarget(backHdc_, hdc_);
	}

	void Application::ClearRenderTarget()
	{
		Rectangle(backHdc_, -1, -1, width_ + 1, height_ + 1); // 흰 사각형을 전체에 채워 그림
	}

	void Application::CopyRenderTarget(HDC source, HDC dest)
	{
		BitBlt(dest, 0, 0, width_, height_, source, 0, 0, SRCCOPY);
	}

	void Application::AdjustApplicationWindow(HWND hwnd, UINT width, UINT height)
	{
		hwnd_ = hwnd;
		hdc_ = GetDC(hwnd_);

		RECT rect = { 0, 0, width, height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		width_ = rect.right - rect.left;
		height_ = rect.bottom - rect.top;

		SetWindowPos(hwnd_, nullptr, 0, 0, width_, height_, 0);
		ShowWindow(hwnd_, true);
	}

	void Application::CreateBackBuffer()
	{
		//윈도우 해상도에 맞게 백버퍼 생성 (캔버스)
		backBitMap_ = CreateCompatibleBitmap(hdc_, width_, height_);
		backHdc_ = CreateCompatibleDC(hdc_);

		HBITMAP oldBitMap = (HBITMAP)SelectObject(backHdc_, backBitMap_);
		DeleteObject(oldBitMap);
	}
}