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

			activeScene_ = scene;//�ӽ� �ڵ� ���߿� �����ϱ�


			scene->Initialize();

			scenes_.insert(std::make_pair(name, scene));

			return scene;
		}

		static Scene* LoadScene(const std::wstring name);
		static Scene* GetActiveScene() { return activeScene_; }

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);
	private:
		static std::map<std::wstring, Scene*> scenes_;

		static Scene* activeScene_;
	};
}