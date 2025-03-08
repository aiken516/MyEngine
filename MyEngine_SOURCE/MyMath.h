#pragma once

namespace Source::Math
{
	struct Vector2
	{
	public:
		static Vector2 one;
		static Vector2 zero;

		static Vector2 up;
		static Vector2 down;
		static Vector2 right;
		static Vector2 left;

		float x;
		float y;

		Vector2()
			: x(0.0f)
			, y(0.0f)
		{

		}

		Vector2(float xParam, float yParam)
			: x(xParam)
			, y(yParam)
		{

		}
	};
}