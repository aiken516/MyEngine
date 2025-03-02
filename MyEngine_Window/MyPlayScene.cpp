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
			Player* background = new Player();
			Transform* transform
				= background->AddComponent<Transform>();
			transform->SetPosition(Vector2(0, 0));

			transform->SetName(L"TR");

			SpriteRenderer* spriteRenderer
				= background->AddComponent<SpriteRenderer>();
			spriteRenderer->SetName(L"SR");
			spriteRenderer->ImageLoad(
				L"C:\\Users\\User\\Documents\\GitHub\\MyEngine\\Resources\\background.png"
			);

			AddGameObject(background);
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