#pragma once
#include "..\\MyEngine_SOURCE\\MySceneManager.h"
#include "MyPlayScene.h"

namespace Source
{
	void LoadScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");

		SceneManager::LoadScene(L"PlayScene");
	}
}