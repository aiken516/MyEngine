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
	/// ���� �ε��� ��(DontDestroyOnLoad ����)�� �ִ� ��� ������Ʈ�� ��ȯ�ϴ� �Լ�
	/// </summary>
	/// <param name="layerType">��ȯ�� ������Ʈ���� ���̾�</param>
	/// <returns>���� �ε��� ���� �ִ� ��� ������Ʈ</returns>
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