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

		void SetOwner(GameObject* owner) { owner_ = owner; }
		GameObject* GetOwner() { return owner_; }

	private:
		GameObject* owner_;
	};
}

