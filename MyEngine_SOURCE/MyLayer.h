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
		virtual void Render(HDC hdc);
		virtual void Destroy();

		void AddGameObject(GameObject* gameObject);
	private:
		//LayerType type_;
		std::vector<GameObject*> _gameObjects;
	};

	typedef std::vector<GameObject*>::iterator GameObjectIter;
}