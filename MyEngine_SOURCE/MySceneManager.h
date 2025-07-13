#pragma once
#include "MyScene.h"

namespace Source
{
	class SceneManager
	{
	public:
		template <typename T>
		static Scene* CreateScene(const std::wstring& name)
		{
			T* scene = new T();
			scene->SetName(name);

			_activeScene = scene;//�ӽ� �ڵ� ���߿� �����ϱ�

			scene->Initialize();

			_scenes.insert(std::make_pair(name, scene));

			return scene;
		}

		static Scene* LoadScene(const std::wstring name);
		static Scene* GetActiveScene() { return _activeScene; }
		static Scene* GetDontDestroyOnLoad() { return _dontDestroyOnLoad; }
		static std::vector<GameObject*> GetGameObjectsOnScene(LayerType layerType);

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
		static void Destroy();

		static void Release();
	private:
		static std::map<std::wstring, Scene*> _scenes;

		static Scene* _activeScene;
		static Scene* _dontDestroyOnLoad;
	};
}