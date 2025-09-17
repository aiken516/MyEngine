#include "MySpriteRenderer.h"
#include "MyGameObject.h"
#include "MyTransform.h"
#include "MyTexture.h"
#include "MyRenderer.h"
#include "MyApplication.h"
#include "MyRenderManager.h"

#include <windows.h>  // 기본 Windows API 헤더
#include <Shlwapi.h>  // PathFileExists()가 선언된 헤더
#include <iostream>

#pragma comment(lib, "Shlwapi.lib")  // 라이브러리 링크

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

		if (Renderer::MainCamera != nullptr)
		{
			position = Renderer::MainCamera->CalculatePostion(position);
		}

		float leftTopX = position.x - (width * scale.x * 0.5f);
		float leftTopY = position.y - (height * scale.x * 0.5f);

		float rightBottomX = position.x + (width * scale.x * 0.5f);
		float rightBottomY = position.y + (height * scale.y * 0.5f);

		if (leftTopX > application.GetWidth() || rightBottomX < 0.0f ||
			leftTopY > application.GetHeight() || rightBottomY < 0.0f)
		{
			return; // 화면 밖에 있으면 렌더링하지 않음
		}

		D2D1_MATRIX_3X2_F rotationMatrix = D2D1::Matrix3x2F::Rotation(
			rotation,
			D2D1::Point2F(position.x, position.y) // 회전의 중심점
		);

		D2D1_MATRIX_3X2_F scaleMatrix = D2D1::Matrix3x2F::Scale(
			D2D1::SizeF(scale.x, scale.y),
			D2D1::Point2F(position.x, position.y) // 크기 변환의 중심점
		);

		D2D1_MATRIX_3X2_F translationMatrix = D2D1::Matrix3x2F::Translation(
			position.x, position.y
		);

		//변환 행렬 조합 (스케일 -> 회전 -> 위치)
		D2D1_MATRIX_3X2_F finalTransform = scaleMatrix * rotationMatrix * translationMatrix;

		RenderRequest request{};
		request.texture = _texture;
		request.sourceRect = D2D1::RectF(0.0f, 0.0f, (float)width, (float)height);
		request.transformMatrix = finalTransform;

		// RenderManager에 렌더링 요청 제출
		RenderManager::AddRenderRequest(request);
	}
}