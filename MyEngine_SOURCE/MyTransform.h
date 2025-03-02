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
			position_.x = x;
			position_.y = y;
		}
		void SetPosition(Vector2 position) 
		{ 
			position_.x = position.x;
			position_.y = position.y;
		}

		Vector2 GetPosition() { return position_; }

	private:
		Vector2 position_;
	};
}
