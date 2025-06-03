#pragma once
#include "MyEntity.h"

namespace Source
{
	using namespace Enums;

	class GameObject;
	class Component : public Entity
	{
	public:
		Component(Enums::ComponentType type);
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void SetOwner(GameObject* owner) { _owner = owner; }
		GameObject* GetOwner() { return _owner; }
		Enums::ComponentType GetType() { return _type; }

	private:
		GameObject* _owner;
		Enums::ComponentType _type;
	};
}

