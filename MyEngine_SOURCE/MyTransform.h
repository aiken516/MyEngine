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
		void Render()  override;

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

		Vector2 GetPosition() const { return _position; }

		void SetScale(int x, int y)
		{
			_scale.x = x;
			_scale.y = y;
		}

		void SetScale(Vector2 scale)
		{
			_scale.x = scale.x;
			_scale.y = scale.y;
		}

		Vector2 GetScale() const { return _scale; }

		void SetRotation(float rotation)
		{
			_rotation = rotation;
		}

		float GetRotation() const { return _rotation; }

	private:
		Vector2 _position;
		Vector2 _scale;
		float _rotation;//실제로는 float와 같게 이용됨, 추후 여러 방향 회전 추가 필요할 수도
	};
}
