#pragma once
#include "CommonInclude.h"

namespace Source::Math
{
	#define PI 3.14159265358979323846f

	struct Vector2
	{
	public:
		static Vector2 one;
		static Vector2 zero;

		static Vector2 up;
		static Vector2 down;
		static Vector2 right;
		static Vector2 left;

		static float Dot(Vector2& leftVector, Vector2& rightVector)
		{
			return (leftVector.x * rightVector.x) + (leftVector.y * rightVector.y);
		}

		static float Cross(Vector2& leftVector, Vector2& rightVector)
		{
			return (leftVector.x * rightVector.y) - (leftVector.y * rightVector.x);
		}

		static Vector2 Rotate(Vector2 vector, float degree)
		{
			float radian = (degree / 180.f) * PI;
			vector.Normalize();
			float x = cosf(radian) * vector.x - sinf(radian) * vector.y;
			float y = sinf(radian) * vector.x + cosf(radian) * vector.y;

			return Vector2(x, y);
		}

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

		Vector2 operator-()
		{
			return Vector2(-x, -y);
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

		void operator-=(Vector2 other)
		{
			x -= other.x;
			y -= other.y;
		}

		Vector2 operator+(Vector2 other)
		{
			return Vector2(x + other.x, y + other.y);
		}
		
		void operator+=(Vector2 other)
		{
			x += other.x;
			y += other.y;
		}

		bool operator==(Vector2 other)
		{
			return (x == other.x && y == other.y);
		}

		void Clear()
		{
			x = 0.0f;
			y = 0.0f;
		}

		float Length()
		{
			return sqrtf(x * x + y * y);
		}

		Vector2 Normalize()
		{
			float length = Length();

			if (length == 0.0f)
			{
				return Vector2(0.0f, 0.0f);
			}

			x = x / length;
			y = y / length;

			return *this;
		}
	};
}