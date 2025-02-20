#include "MyApplication.h"
#include "MyInput.h"
#include "MyTime.h"

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
		hwnd_ = hwnd;
		hdc_ = GetDC(hwnd_);

		RECT rect = { 0, 0, width, height };
		AdjustWindowRect(&rect , WS_OVERLAPPEDWINDOW, false);

		width_ = rect.right - rect.left;
		height_ = rect.bottom - rect.top;

		SetWindowPos(hwnd_, nullptr, 0, 0, width_, height_, 0);
		ShowWindow(hwnd_, true);

		//������ �ػ󵵿� �°� ����� ���� (ĵ����)
		backBitMap_ = CreateCompatibleBitmap(hdc_, width_, height_);
		backHdc_ = CreateCompatibleDC(hdc_);

		HBITMAP oldBitMap = (HBITMAP)SelectObject(backHdc_, backBitMap_);
		DeleteObject(oldBitMap);

		Input::Initailize();	
		Time::Initailze();

		player_.SetPosition(0, 0);
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
		player_.Update();
	}

	void Application::LateUpdate()
	{
		player_.LateUpdate();

	}

	void Application::Render()
	{
		Rectangle(backHdc_, 0, 0, 1600, 900); // �� �簢���� ��ü�� ä�� �׸�

		player_.Render(backHdc_);
		Time::Render(backHdc_);

		BitBlt(hdc_, 0, 0, width_, height_, backHdc_, 0, 0, SRCCOPY);
	}
}