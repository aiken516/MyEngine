#include "MySpriteRenderer.h"
#include "MyGameObject.h"
#include "MyTransform.h"
#include "MyTexture.h"
#include "MyApplication.h"
#include "MyRenderManager.h"

extern Source::Application application;

namespace Source
{
	SpriteRenderer::SpriteRenderer() :
		Component(Enums::ComponentType::Renderer),
		_texture(nullptr)
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Initialize()
	{
	}

	void SpriteRenderer::Update()
	{
	}

	void SpriteRenderer::LateUpdate()
	{
	}

	void SpriteRenderer::Render()
	{
		if (_texture == nullptr)
		{
			assert(false);
		}

		Transform* transform = GetOwner()->GetComponent<Transform>();

		Vector2 position = transform->GetPosition();
		float rotation = transform->GetRotation();
		Vector2 scale = transform->GetScale();
		UINT width = _texture->GetWidth();
		UINT height = _texture->GetHeight();

		D2D1_MATRIX_3X2_F rotationMatrix = D2D1::Matrix3x2F::Rotation(rotation);
		D2D1_MATRIX_3X2_F scaleMatrix = D2D1::Matrix3x2F::Scale(D2D1::SizeF(scale.x, scale.y));
		D2D1_MATRIX_3X2_F translationMatrix = D2D1::Matrix3x2F::Translation(position.x, position.y);

		D2D1_MATRIX_3X2_F finalTransform = scaleMatrix * rotationMatrix * translationMatrix;

		SpriteRenderRequest request{};
		request.texture = _texture;
		request.sourceRect = D2D1::RectF(0.0f, 0.0f, (float)width, (float)height);
		request.transformMatrix = finalTransform;

		request.size = D2D1::SizeF(width * scale.x, height * scale.y);

		RenderManager::AddSpriteRequest(request);
	}
}