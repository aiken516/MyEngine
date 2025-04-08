#include "MySceneManager.h"

namespace Source
{
	std::map<std::wstring, Scene*> SceneManager::_scenes = {};
	Scene* SceneManager::_activeScene = nullptr;

	Scene* SceneManager::LoadScene(const std::wstring name)
	{
		if (_activeScene != nullptr)
		{
			_activeScene->OnExit();
		}

		std::map<std::wstring, Scene*>::iterator iter = _scenes.find(name);

		if (iter == _scenes.end())
		{
			return nullptr;
		}

		_activeScene = iter->second;

		_activeScene->OnEnter();

		return iter->second;
	}

	void SceneManager::Initialize()
	{
	}

	void SceneManager::Update()
	{
		_activeScene->Update();
	}

	void SceneManager::LateUpdate()
	{
		_activeScene->LateUpdate();
	}

	void SceneManager::Render(HDC hdc)
	{
		_activeScene->Render(hdc);
	}

	void SceneManager::Destroy()
	{
		_activeScene->Destroy();
	}

	void SceneManager::Release()
	{
		for (auto& scene : _scenes)
		{
			if (scene.second != nullptr)
			{
				delete scene.second;
				scene.second = nullptr;
			}
		}
		_scenes.clear();
	}
}