#pragma once
#include "..\\MyEngine_SOURCE\\MyGameObject.h"
using namespace Source;

namespace Client
{
	class Player : public GameObject
	{
	public:
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:

	};
}
