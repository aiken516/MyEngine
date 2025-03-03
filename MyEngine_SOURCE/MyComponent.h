#pragma once
#include "MyEntity.h"

namespace Source
{
	class GameObject;
	class Component : public Entity
	{
	public:
		Component();
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void SetOwner(GameObject* owner) { _owner = owner; }
		GameObject* GetOwner() { return _owner; }

	private:
		GameObject* _owner;
	};
}

