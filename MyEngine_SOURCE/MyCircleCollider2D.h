#pragma once
#include "MyCollider.h"

namespace Source
{
	class CircleCollider2D : public Collider
	{
	public:
		CircleCollider2D();
		~CircleCollider2D();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		bool Intersect(Collider* other) override;
		bool IntersectWithCircle(class CircleCollider2D* other) override;
		bool IntersectWithBox(class BoxCollider2D* other) override;
	private:
		Math::Vector2 _center;
		float _radius;

	};
}
