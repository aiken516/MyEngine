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
		virtual void Render();
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

		void CreateLayers();
		Layer* GetLayer(const Enums::LayerType layerType) { return _sceneLayers[(UINT)layerType]; }
		void RemoveGameObject(GameObject* gameObject);
		void AddGameObject(GameObject* gameObject, const Enums::LayerType layerType);
	private:
		std::vector<Layer*> _sceneLayers;
	};
}
