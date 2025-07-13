#pragma once
#include "..\\MyEngine_SOURCE\\MyScene.h"
using namespace Source;

namespace Client
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void OnEnter() override;
		void OnExit() override;
	private:
	};
}