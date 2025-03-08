#include "MyPlayScene.h"
#include "MyGameObject.h"
#include "MyPlayer.h"
#include "MyTransform.h"
#include "MySpriteRenderer.h"
#include "MyInput.h"
#include "MySceneManager.h"
#include "MyObject.h"
#include "MyTexture.h"
#include "MyResources.h"

namespace Client
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
			Player* background = Object::Instantiate<Player>(
				Enums::LayerType::Background, Vector2(10.0f, 10.0f));

			SpriteRenderer* spriteRenderer
				= background->AddComponent<SpriteRenderer>();
			spriteRenderer->SetName(L"SR");

			spriteRenderer->SetTexture(Resources::Find<Graphics::Texture>(L"background"));

			Scene::Initialize();
		}
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (Input::GetKeyDown(KeyCode::R))
		{
			SceneManager::LoadScene(L"TitleScene");
		}
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t str[50] = L"";

		swprintf_s(str, 50, L"Play Scene");
		TextOut(hdc, 200, 200, str, wcsnlen_s(str, 50));
	}

	void PlayScene::OnEnter()
	{
	}

	void PlayScene::OnExit()
	{
	}
}