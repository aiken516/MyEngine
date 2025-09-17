#pragma once
#include "MyEntity.h"
#include "MyComponent.h"
#include "MyTexture.h"

namespace Source
{
	class TextRenderer : public Component
	{
	public:
		TextRenderer();
		~TextRenderer();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render()  override;

		void SetText(const std::wstring& text) { _text = text; }
		void SetColor(const D2D1_COLOR_F& color) { _color = color; }
		
		void SetTextRect(float left, float top, float right, float bottom)
		{
			_textRect = D2D1::RectF(left, top, right, bottom);
		}

		void SetFontSize(float size);
	private:
		std::wstring _text;
		D2D1_RECT_F _textRect;
		D2D1_COLOR_F _color;
		float _fontSize;
		IDWriteTextFormat* _textFormat;
	};
}