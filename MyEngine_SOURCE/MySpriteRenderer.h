#pragma once
#include "MyEntity.h"
#include "MyComponent.h"

namespace Source
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;

		void ImageLoad(const std::wstring& path);
	private:
		Gdiplus::Image* _sprite;
		UINT _width;
		UINT _height;
	};
}
