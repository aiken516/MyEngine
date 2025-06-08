#include "MySceneManager.h"
#include "MyDontDestroyOnLoad.h"

namespace Source
{
	std::map<std::wstring, Scene*> SceneManager::_scenes = {};
	Scene* SceneManager::_activeScene = nullptr;
	Scene* SceneManager::_dontDestroyOnLoad = nullptr;

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

	/// <summary>
	/// 현재 로딩된 씬(DontDestroyOnLoad 포함)에 있는 모든 오브젝트를 반환하는 함수
	/// </summary>
	/// <param name="layerType">반환할 오브젝트들의 레이어</param>
	/// <returns>현재 로딩된 씬에 있는 모든 오브젝트</returns>
	std::vector<GameObject*> SceneManager::GetGameObjectsOnScene(LayerType layerType)
	{
		std::vector<GameObject*> gameObjects = _activeScene->GetLayer(layerType)->GetGameObjects();
		std::vector<GameObject*> dontDestroyGameObjects = _dontDestroyOnLoad->GetLayer(layerType)->GetGameObjects();

		gameObjects.insert(
			gameObjects.end(),
			dontDestroyGameObjects.begin(),
			dontDestroyGameObjects.end()
		);

		return gameObjects;
	}

	void SceneManager::Initialize()
	{
		_dontDestroyOnLoad = CreateScene<DontDestroyOnLoad>(L"DontDestroyOnLoad");
	}

	void SceneManager::Update()
	{
		_activeScene->Update();
		_dontDestroyOnLoad->Update();
	}

	void SceneManager::LateUpdate()
	{
		_activeScene->LateUpdate();
		_dontDestroyOnLoad->LateUpdate();
	}

	void SceneManager::Render(HDC hdc)
	{
		_activeScene->Render(hdc);
		_dontDestroyOnLoad->Render(hdc);
	}

	void SceneManager::Destroy()
	{
		_activeScene->Destroy();
		_dontDestroyOnLoad->Destroy();
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