#pragma once
#include "..\\MyEngine_SOURCE\\MyScene.h"

namespace Source
{
	class LoadingScene : public Scene
	{
	public:
		LoadingScene();
		~LoadingScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void OnEnter() override;
		void OnExit()  override;

	private:
		void ResourcesLoad(std::mutex& mutex);

		bool _isLoadCompleted;
		std::thread* _resourcesLoadThread;
		std::mutex _mutex;
	};
}