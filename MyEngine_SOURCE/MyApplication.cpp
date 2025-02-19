#include "MyApplication.h"
#include "MyInput.h"

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
		player.Update();
	}

	void Application::LateUpdate()
	{
		player.LateUpdate();

	}

	void Application::Render()
	{
		player.Render(mHDC);
	}
}