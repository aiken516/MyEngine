#pragma once
#include "..\\MyEngine_SOURCE\\MySceneManager.h"
using namespace Source;

#include "MyPlayScene.h"
#include "MyTitleScene.h"
#include "MyLoadingScene.h"

namespace Client
{
	void LoadScenes()
	{
		SceneManager::CreateScene<LoadingScene>(L"LoadingScene");

		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<TitleScene>(L"TitleScene");

		SceneManager::LoadScene(L"LoadingScene");
	}
}