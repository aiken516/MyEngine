#pragma once
#include "..\\MyEngine_SOURCE\\MyScript.h"
using namespace Source;

namespace Client
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;
	private:

	};
}
