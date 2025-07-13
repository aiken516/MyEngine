#pragma once
#include "CommonInclude.h"
#include "MyEntity.h"
#include "MyGameObject.h"

namespace Source
{
	class Layer : public Entity
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destroy();

		const std::vector<GameObject*>& GetGameObjects() { return _gameObjects; }

		void AddGameObject(GameObject* gameObject);
		void RemoveGameObject(GameObject* gameObject);
	private:
		//LayerType _type;
		std::vector<GameObject*> _gameObjects;
	};

	typedef std::vector<GameObject*>::iterator GameObjectIter;
}