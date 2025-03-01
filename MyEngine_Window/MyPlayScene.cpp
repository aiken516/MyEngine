#include "MyPlayScene.h"
#include "MyGameObject.h"
#include "MyPlayer.h"
#include "MyTransform.h"
#include "MySpriteRenderer.h"

namespace Source
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		{
			Player* player = new Player();
			Transform* transform = player->AddComponent<Transform>();
			transform->SetPosition(800, 450);

			transform->SetName(L"TR");

			SpriteRenderer* spriteRenderer = player->AddComponent<SpriteRenderer>();
			spriteRenderer->SetName(L"SR");

			AddGameObject(player);
		}

		{
			Player* player = new Player();
			Transform* transform = player->AddComponent<Transform>();
			transform->SetPosition(300, 450);

			transform->SetName(L"TR");

			SpriteRenderer* spriteRenderer = player->AddComponent<SpriteRenderer>();
			spriteRenderer->SetName(L"SR");

			AddGameObject(player);
		}

		{
			Player* player = new Player();
			Transform* transform = player->AddComponent<Transform>();
			transform->SetPosition(100, 650);

			transform->SetName(L"TR");

			SpriteRenderer* spriteRenderer = player->AddComponent<SpriteRenderer>();
			spriteRenderer->SetName(L"SR");

			AddGameObject(player);
		}
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}