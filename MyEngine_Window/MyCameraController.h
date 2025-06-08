#pragma once
#include "..\\MyEngine_SOURCE\\MyScript.h"
#include "..\\MyEngine_SOURCE\\MyTransform.h"
using namespace Source;

namespace Client
{
	class CameraController : public Script
	{
	public:
		CameraController();
		~CameraController();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:

	};
}