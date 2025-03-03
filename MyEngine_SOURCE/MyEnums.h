#pragma once

namespace Source::Enums
{
	//랜더링 시 우선 순위를 위한 레이어
	//유니티의 카메라 레이어 비슷한 개념으로 enum
	//랜더링 자체에 우선 순위 인자가 더 있어야 할 수도
	enum class LayerType
	{
		None = 0,
		Background = 1,
		Player = 2,
		//
		MAX = 16
	};
}