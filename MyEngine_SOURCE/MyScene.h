#pragma once
#include "MyEntity.h"
#include "MyGameObject.h"
#include "MyLayer.h"

namespace Source
{
	class Scene : public Entity
	{
	public:
		Scene();
		~Scene();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		virtual void OnEnter();
		virtual void OnExit();

		void CreateLayers();
		void AddGameObject(GameObject* gameObject, LayerType layerType);
	private:
		std::vector<Layer*> layers_;
	};
}
