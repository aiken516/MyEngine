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

		Vector2 operator*(float value)
		{
			return Vector2(x * value, y * value);
		}

		Vector2 operator/(float value)
		{
			return Vector2(x / value, y / value);
		}

		Vector2 operator-(Vector2 other)
		{
			return Vector2(x - other.x, y - other.y);
		}

		Vector2 operator+(Vector2 other)
		{
			return Vector2(x + other.x, y + other.y);
		}
	};
}