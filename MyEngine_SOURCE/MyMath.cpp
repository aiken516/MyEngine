#include "MyMath.h"

namespace Source::Math
{
	Vector2 Vector2::one = Vector2 (1.0f, 1.0f);
	Vector2 Vector2::zero = Vector2 (0.0f, 0.0f);

	Vector2 Vector2::up = Vector2 (0.0f, 1.0f);
	Vector2 Vector2::down = Vector2 (0.0f, -1.0f);
	Vector2 Vector2::right = Vector2 (1.0f, 0.0f);
	Vector2 Vector2::left = Vector2 (-1.0f, 0.0f);
}