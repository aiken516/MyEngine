#include "MySceneManager.h"

namespace Source
{
	std::map<std::wstring, Scene*> SceneManager::scenes_ = {};
	Scene* SceneManager::activeScene_ = nullptr;

	Scene* SceneManager::LoadScene(const std::wstring name)
	{
		if (activeScene_ != nullptr)
		{
			activeScene_->OnExit();
		}

		std::map<std::wstring, Scene*>::iterator iter = scenes_.find(name);

		if (iter == scenes_.end())
		{
			return nullptr;
		}

		activeScene_ = iter->second;

		activeScene_->OnEnter();

		return iter->second;
	}

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