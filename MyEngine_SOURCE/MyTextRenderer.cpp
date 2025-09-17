#include "MyTextRenderer.h"
#include "MyGameObject.h"
#include "MyTransform.h"
#include "MyTexture.h"
#include "MyApplication.h"
#include "MyRenderManager.h"

extern Source::Application application;

namespace Source
{
	TextRenderer::TextRenderer() :
		Component(Enums::ComponentType::Renderer),
		_text(L""),
		_textRect(D2D1::RectF(0.0f, 0.0f, 200.0f, 50.0f)),
		_color(D2D1::ColorF(D2D1::ColorF::Black)),
		_fontSize(12.0f),
		_textFormat(nullptr)
	{
	}

	TextRenderer::~TextRenderer()
	{
	}

	void TextRenderer::Initialize()
	{
		SetFontSize(_fontSize);
	}

	void TextRenderer::Update()
	{
	}

	void TextRenderer::LateUpdate()
	{
	}

	void TextRenderer::Render()
	{
		if (_text.empty() || _textFormat == nullptr)
		{
			return;
		}

		Transform* transform = GetOwner()->GetComponent<Transform>();
		Vector2 position = transform->GetPosition();
		Vector2 scale = transform->GetScale();
		float rotation = transform->GetRotation();

		D2D1_MATRIX_3X2_F scaleMatrix = D2D1::Matrix3x2F::Scale(scale.x, scale.y);
		D2D1_MATRIX_3X2_F rotationMatrix = D2D1::Matrix3x2F::Rotation(rotation);
		D2D1_MATRIX_3X2_F translationMatrix = D2D1::Matrix3x2F::Translation(position.x, position.y);

		TextRequest request{};
		request.text = _text;
		request.textRect = _textRect;
		request.color = _color;
		request.textFormat = _textFormat;
		request.transformMatrix = scaleMatrix * rotationMatrix * translationMatrix;

		RenderManager::AddTextRequest(request);
	}

	void TextRenderer::SetFontSize(float size)
	{
		_fontSize = size;

		HRESULT hr = application.GetGraphicDevice()->GetDWriteFactory()->CreateTextFormat(
			L"Arial",
			NULL,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			_fontSize,
			L"ko-KR",
			&_textFormat
		);

		if (FAILED(hr))
		{
			assert(false);
		}
	}
}