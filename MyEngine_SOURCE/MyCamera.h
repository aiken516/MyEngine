#pragma once
#include "MyEntity.h"
#include "MyComponent.h"

namespace Source
{
	class Camera : public Component
	{
	public:
		Camera();
		~Camera();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render()  override;

		D2D1_MATRIX_3X2_F GetViewMatrix();

		void SetTarget(GameObject* target) { _target = target; }
	private:
		class GameObject* _target;// �����ϴ� ������Ʈ, ���漱��

		Vector2 _resolution;
	};
}