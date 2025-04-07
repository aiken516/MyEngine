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
#include "MyCamera.h"
#include "MyRenderer.h"
#include "MyPlayerScript.h"
#include "MyAnimator.h"

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
			GameObject* camera = Object::Instantiate<GameObject>(
				Enums::LayerType::None, Vector2(0.0f, 10.0f));
			Camera* cameraComponent = camera->AddComponent<Camera>();
			Renderer::MainCamera = cameraComponent;
			camera->AddComponent<PlayerScript>();


			GameObject* background = Object::Instantiate<GameObject>(
				Enums::LayerType::Particle, Vector2(10.0f, 100.0f));

			SpriteRenderer* spriteRenderer = background->AddComponent<SpriteRenderer>();
			spriteRenderer->SetName(L"SR");
			spriteRenderer->SetTexture(Resources::Find<Graphics::Texture>(L"Punch"));

			/*GameObject* pacman = Object::Instantiate<GameObject>(
				Enums::LayerType::Background, Vector2(30.0f, 30.0f));

			SpriteRenderer* pacmanSpriteRenderer = pacman->AddComponent<SpriteRenderer>();
			pacmanSpriteRenderer->SetName(L"SR");
			pacmanSpriteRenderer->SetTexture(Resources::Find<Graphics::Texture>(L"Cat"));
			pacmanSpriteRenderer->SetSize(Vector2(3.0f, 3.0f));

			pacman->AddComponent<PlayerScript>();*/

			GameObject* cat = Object::Instantiate<GameObject>(
				Enums::LayerType::Background, Vector2(30.0f, 100.0f));

			cat->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));

			Animator* animator =cat->AddComponent<Animator>();
			animator->CreateAnimation(L"CatFrontMove", Resources::Find<Graphics::Texture>(L"Cat"),
				Vector2::zero, Vector2::zero, Vector2(32.0f, 32.0f), 4, 0.4f);

			animator->PlayAnimation(L"CatFrontMove", true);
			cat->AddComponent<PlayerScript>();


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