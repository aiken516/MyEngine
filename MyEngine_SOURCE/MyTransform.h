#pragma once
#include "MyEntity.h"
#include "MyComponent.h"

namespace Source
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;

		void SetPosition(int x, int y) { x_ = x; y_ = y; }
		int GetX() { return x_; }
		int GetY() { return y_; }
	private:
		int x_;
		int y_;
	};
}
