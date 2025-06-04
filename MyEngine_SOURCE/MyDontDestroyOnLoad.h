#pragma once

#include "MyScene.h"

namespace Source
{
	class DontDestroyOnLoad : public Scene
	{
	public:
		DontDestroyOnLoad();
		~DontDestroyOnLoad();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();
	};
}