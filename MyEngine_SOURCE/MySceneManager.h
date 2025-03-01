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
			scene->Initialize();

			scenes_.insert(std::make_pair(name, scene));

			return scene;
		}

		static Scene* LoadScene(const std::wstring name)
		{
			std::map<std::wstring, Scene*>::iterator iter = scenes_.find(name);

			if (iter == scenes_.end())
			{
				return nullptr;
			}

			activeScene_ = iter->second;

			return iter->second;
		}

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);
	private:
		static std::map<std::wstring, Scene*> scenes_;

		static Scene* activeScene_;
	};
}