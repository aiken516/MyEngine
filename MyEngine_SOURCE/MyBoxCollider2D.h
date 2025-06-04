#pragma once
#include "MyCollider.h"

namespace Source
{
	class BoxCollider2D : public Collider
	{
	public:
		BoxCollider2D();
		~BoxCollider2D();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		bool Intersect(Collider* other) override;
		bool IntersectWithCircle(class CircleCollider2D* other) override;
		bool IntersectWithBox(class BoxCollider2D* other) override;
	private:
	};
}
