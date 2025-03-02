#pragma once

namespace Source::Math
{
	struct Vector2
	{
	public:
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