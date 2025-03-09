#pragma once
#include "MyEntity.h"
#include "MyComponent.h"

namespace Source
{
	class Script : public Component
	{
	public:
		Script();
		~Script();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;
	private:

	};
}


