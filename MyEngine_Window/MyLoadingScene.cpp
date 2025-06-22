#include "MyLoadingScene.h"
#include "MySceneManager.h"
#include "MyResources.h"
#include "MyTexture.h"
#include "MyAudioClip.h"

namespace Source
{
	LoadingScene::LoadingScene() :
		_isLoadCompleted(false),
		_resourcesLoadThread(),
		_mutex()
	{
	}

	LoadingScene::~LoadingScene()
	{
		delete _resourcesLoadThread;
		_resourcesLoadThread = nullptr;
	}

	void LoadingScene::Initialize()
	{
		_resourcesLoadThread = new std::thread(&LoadingScene::ResourcesLoad, this, std::ref(_mutex));
	}

	void LoadingScene::Update()
	{
		if (_isLoadCompleted)
		{
			_resourcesLoadThread->join();

			SceneManager::LoadScene(L"PlayScene"); // 씬 이름을 동적으로 처리해야할 수도
		}
	}

	void LoadingScene::LateUpdate()
	{
	}

	void LoadingScene::Render(HDC hdc)
	{
	}

	void LoadingScene::OnEnter()
	{
	}

	void LoadingScene::OnExit()
	{
	}

	void LoadingScene::ResourcesLoad(std::mutex& mutex)
	{
		mutex.lock();
		{
			Resources::Load<Graphics::Texture>(L"background", L"..\\Resources\\background.png");
			Resources::Load<Graphics::Texture>(L"Pacman", L"..\\Resources\\Pacman\\0.png");
			Resources::Load<Graphics::Texture>(L"Chicken", L"..\\Resources\\chicken.bmp");
			Resources::Load<Graphics::Texture>(L"Cat", L"..\\Resources\\CatAlpha.bmp");
			Resources::Load<Graphics::Texture>(L"Punch", L"..\\Resources\\Punch.png");
			Resources::Load<Graphics::Texture>(L"Mushroom1", L"..\\Resources\\Mushroom\\1.bmp");
			Resources::Load<Graphics::Texture>(L"Mushroom2", L"..\\Resources\\Mushroom\\2.bmp");
			Resources::Load<Graphics::Texture>(L"Mushroom3", L"..\\Resources\\Mushroom\\3.bmp");

			Resources::Load<AudioClip>(L"BGSound", L"..\\Resources\\Sounds\\BGM.wav");
		}
		mutex.unlock();

		// complete
		_isLoadCompleted = true;
	}
}