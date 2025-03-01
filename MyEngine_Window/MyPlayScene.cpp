#include "MyPlayScene.h"
#include "MyGameObject.h"

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
		//Scene::Initialize();
		GameObject* gameObject = new GameObject();
		AddGameObject(gameObject);
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