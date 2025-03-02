#pragma once
#include "..\\MyEngine_SOURCE\\MyScene.h"
using namespace Source;

namespace Client
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
	private:
	};
}

