#include "MyApplication.h"
#include "MyInput.h"
#include "MyTime.h"

namespace Source
{
	Application::Application() :
		mHWND(nullptr),
		mHDC(nullptr)
	{

	}

	Application::~Application()
	{
	
	}

	void Application::Initialize(HWND hwnd)
	{
		mHWND = hwnd;
		mHDC = GetDC(mHWND);

		Input::Initailize();	
		Time::Initailze();

		player.SetPosition(0, 0);
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
		player.Update();
	}

	void Application::LateUpdate()
	{
		player.LateUpdate();

	}

	void Application::Render()
	{
		player.Render(mHDC);
		Time::Render(mHDC);
	}
}