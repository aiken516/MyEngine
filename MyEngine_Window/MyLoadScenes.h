#pragma once
#include "..\\MyEngine_SOURCE\\MySceneManager.h"
using namespace Source;

#include "MyPlayScene.h"
#include "MyTitleScene.h"
#include "MyToolScene.h"

namespace Client
{
	void LoadScenes()
	{
		//SceneManager::CreateScene<PlayScene>(L"PlayScene");
		//SceneManager::CreateScene<TitleScene>(L"TitleScene");

		SceneManager::CreateScene<ToolScene>(L"ToolScene");

		SceneManager::LoadScene(L"ToolScene");
	}
}