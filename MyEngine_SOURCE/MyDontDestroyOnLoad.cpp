#include "MyDontDestroyOnLoad.h"

namespace Source
{
	DontDestroyOnLoad::DontDestroyOnLoad()
	{
	}

	DontDestroyOnLoad::~DontDestroyOnLoad()
	{
	}

	void DontDestroyOnLoad::Initialize()
	{
		Scene::Initialize();
	}

	void DontDestroyOnLoad::Update()
	{
		Scene::Update();
	}

	void DontDestroyOnLoad::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void DontDestroyOnLoad::Render()
	{
		Scene::Render();
	}

	void DontDestroyOnLoad::Destroy()
	{
		Scene::Destroy();
	}

	void DontDestroyOnLoad::OnEnter()
	{
		Scene::OnEnter();
	}

	void DontDestroyOnLoad::OnExit()
	{
		Scene::OnExit();
	}
}