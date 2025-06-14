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
		void Render(HDC hdc)  override;

		void SetTarget(GameObject* target) { _target = target; }

		Vector2 CalculatePostion(Vector2 objectPosition) const { return objectPosition - _distance; }
		Vector2 CalculateMousePostion(Vector2 objectPosition) const { return objectPosition + _distance; }
	private:
		//std::vector<GameObject*> _gameObjects;
		class GameObject* _target;// 추적하는 오브젝트, 전방선언

		Vector2 _distance;
		Vector2 _resolution;
		Vector2 _lookPosition;
	};
}