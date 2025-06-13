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
#include "MyBoxCollider2D.h"
#include "MyCircleCollider2D.h"
#include "MyCollisionManager.h"
#include "MyRigidBody2D.h"
#include "MyAudioListener.h"
#include "MyAudioSource.h"
#include "MyAudioClip.h"

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
			// -------------------- 충돌체 설정 ---------------
			CollisionManager::SetCollisionLayerMatrix(LayerType::Background, LayerType::Background, true);


			// -------------------- 카메라 --------------------
			GameObject* camera = Object::Instantiate<GameObject>(
				Enums::LayerType::None, Vector2(0.0f, 10.0f));
			Camera* cameraComponent = camera->AddComponent<Camera>();
			Renderer::MainCamera = cameraComponent;

			// ------------------- 배경 -------------------

			GameObject* background = Object::Instantiate<GameObject>(
				Enums::LayerType::Particle, Vector2(10.0f, 100.0f));

			SpriteRenderer* spriteRenderer = background->AddComponent<SpriteRenderer>();
			spriteRenderer->SetName(L"SR");
			spriteRenderer->SetTexture(Resources::Find<Graphics::Texture>(L"Punch"));

			// ------------------- 고양이 -------------------

			GameObject* cat = Object::Instantiate<GameObject>(
				Enums::LayerType::Background, Vector2(30.0f, -200.0f));

			cat->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));

			cat->AddComponent<AudioListener>();

			Animator* animator = cat->AddComponent<Animator>();
			animator->CreateAnimation(L"CatFrontMove", Resources::Find<Graphics::Texture>(L"Cat"),
				Vector2::zero, Vector2::zero, Vector2(32.0f, 32.0f), 4, 0.4f);

			animator->PlayAnimation(L"CatFrontMove", true);
			cat->AddComponent<PlayerScript>();

			CircleCollider2D* collider = cat->AddComponent<CircleCollider2D>();
			collider->SetRadius(0.5f);
			//BoxCollider2D* collider = cat->AddComponent<BoxCollider2D>();

			RigidBody2D* rigidBody2D = cat->AddComponent<RigidBody2D>();
			rigidBody2D->SetMass(1.0f);
			rigidBody2D->SetUseGravity(false);

			cameraComponent->SetTarget(cat);

			//Object::DontDestroyOnLoad(cat);

			// ---------------- 배경 고양이 ----------------
			GameObject* backgroundCat = Object::Instantiate<GameObject>(
				Enums::LayerType::Background, Vector2(60.0f, 250.0f));

			backgroundCat->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));

			Animator* backgroundCatAnimator = backgroundCat->AddComponent<Animator>();
			backgroundCatAnimator->CreateAnimation(L"CatFrontMove", Resources::Find<Graphics::Texture>(L"Cat"),
				Vector2::zero, Vector2::zero, Vector2(32.0f, 32.0f), 4, 0.4f);

			backgroundCatAnimator->PlayAnimation(L"CatFrontMove", true);
			BoxCollider2D* backgroundCatCollider = backgroundCat->AddComponent<BoxCollider2D>();
			//CircleCollider2D* backgroundCatCollider = backgroundCat->AddComponent<CircleCollider2D>();

			//RigidBody2D* backgroundCatRigidBody2D = backgroundCat->AddComponent<RigidBody2D>();
			//backgroundCatRigidBody2D->SetMass(1.0f);
			//backgroundCatRigidBody2D->SetUseGravity(false);

			AudioSource* backgroundCatAudioSource = backgroundCat->AddComponent<AudioSource>();
			backgroundCatAudioSource->SetAudioClip(Resources::Find<AudioClip>(L"BGSound"));
			backgroundCatAudioSource->Play();

			// ---------------- 배경 고양이 2 ----------------
			GameObject* backgroundCat2 = Object::Instantiate<GameObject>(
				Enums::LayerType::Background, Vector2(240.0f, 250.0f));

			backgroundCat2->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));

			Animator* backgroundCat2Animator = backgroundCat2->AddComponent<Animator>();
			backgroundCat2Animator->CreateAnimation(L"CatFrontMove", Resources::Find<Graphics::Texture>(L"Cat"),
				Vector2::zero, Vector2::zero, Vector2(32.0f, 32.0f), 4, 0.4f);

			backgroundCat2Animator->PlayAnimation(L"CatFrontMove", true);
			BoxCollider2D* backgroundCat2Collider = backgroundCat2->AddComponent<BoxCollider2D>();
			//CircleCollider2D* backgroundCatCollider = backgroundCat->AddComponent<CircleCollider2D>();

			//RigidBody2D* backgroundCatRigidBody2D = backgroundCat->AddComponent<RigidBody2D>();
			//backgroundCatRigidBody2D->SetMass(1.0f);
			//backgroundCatRigidBody2D->SetUseGravity(false);

			AudioSource* backgroundCat2AudioSource = backgroundCat2->AddComponent<AudioSource>();
			backgroundCat2AudioSource->SetAudioClip(Resources::Find<AudioClip>(L"BGSound"));
			backgroundCat2AudioSource->SetIsLoop(true);
			backgroundCat2AudioSource->Play();

			// ------------------- 버섯 -------------------

			GameObject* mushroom = Object::Instantiate<GameObject>(
				Enums::LayerType::Background, Vector2(40.0f, 100.0f));

			mushroom->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));

			Animator* mushroomAnimator = mushroom->AddComponent<Animator>();
			mushroomAnimator->CreateAnimationByFolder(L"Mushroom", L"..\\Resources\\Mushroom",
				Vector2::zero, 5.4f);

			mushroomAnimator->PlayAnimation(L"Mushroom", true);

			// ---------------------------------------------


			// ---------------------------------------------

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