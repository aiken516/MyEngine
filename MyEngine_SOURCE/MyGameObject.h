#pragma once
#include "CommonInclude.h"

namespace Source
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		void Update();
		void LateUpdate();
		void Render(HDC hdc);

		void SetPosition(float x, float y);
		int GetPositionX();
		int GetPositionY();

	private:
		float X;
		float Y;
	};
}


