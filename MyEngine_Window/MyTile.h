#pragma once
#include "..\\MyEngine_SOURCE\\MyGameObject.h"
using namespace Source;

namespace Client
{
	class Tile : public GameObject
	{
	public:
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetPositionByIndex(int x, int y);
	private:

	};
}
