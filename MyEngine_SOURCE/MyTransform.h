#pragma once
#include "MyEntity.h"
#include "MyComponent.h"

namespace Source
{
	using namespace Math;

	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;

		void SetPosition(int x, int y)
		{ 
			_position.x = x;
			_position.y = y;
		}
		void SetPosition(Vector2 position) 
		{ 
			_position.x = position.x;
			_position.y = position.y;
		}

		Vector2 GetPosition() { return _position; }

	private:
		Vector2 _position;
	};
}
