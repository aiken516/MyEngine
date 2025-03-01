#include "MySceneManager.h"

namespace Source
{
	std::map<std::wstring, Scene*> SceneManager::scenes_ = {};
	Scene* SceneManager::activeScene_ = nullptr;

	void SceneManager::Initialize()
	{
	}

	void SceneManager::Update()
	{
		activeScene_->Update();
	}

	void SceneManager::LateUpdate()
	{
		activeScene_->LateUpdate();
	}

	void SceneManager::Render(HDC hdc)
	{
		activeScene_->Render(hdc);
	}
}