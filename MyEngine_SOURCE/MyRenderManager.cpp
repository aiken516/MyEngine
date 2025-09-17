#include "MyRenderManager.h"
#include "MyRenderer.h"
#include "MyApplication.h"

#include <algorithm>

extern Source::Application application;

namespace Source
{
	std::vector<RenderRequest> RenderManager::_renderRequestList = {};
	std::vector<TextRequest> RenderManager::_textRequestList = {};
	std::vector<GizmoRequest> RenderManager::_gizmoRequestList = {};
	ID2D1SolidColorBrush* RenderManager::_brush = nullptr;

	void RenderManager::Initialize()
	{
		HRESULT hr = application.GetGraphicDevice()->GetRenderTarget()->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White, 1.0f),
			&_brush
		);

		if (FAILED(hr))
		{
			assert(false);
		}
	}

	void RenderManager::Update()
	{
	}

	void RenderManager::LateUpdate()
	{
	}

	void RenderManager::Render(ID2D1HwndRenderTarget* renderTarget)
	{
		if (renderTarget == nullptr)
		{
			return;
		}
		D2D1_MATRIX_3X2_F cameraMatrix = Renderer::MainCamera->GetViewMatrix();

		RenderSprites(renderTarget, cameraMatrix);
		RenderTexts(renderTarget, cameraMatrix);
		RenderGizmos(renderTarget, cameraMatrix);
	}

	void RenderManager::RenderSprites(ID2D1HwndRenderTarget* renderTarget, D2D1_MATRIX_3X2_F cameraMatrix)
	{
		// 텍스처 포인터 주소값 기준 정렬 로직은 유지
		std::sort(_renderRequestList.begin(), _renderRequestList.end(),
			[](const RenderRequest& a, const RenderRequest& b) {
				return a.texture < b.texture;
			});

		for (const auto& request : _renderRequestList)
		{
			if (request.texture != nullptr && request.texture->GetBitmap())
			{
				D2D1_MATRIX_3X2_F finalTransform = request.transformMatrix * cameraMatrix;

				// 위치만 추출 (행렬의 translation 부분)
				float worldX = finalTransform._31;
				float worldY = finalTransform._32;

				D2D1_RECT_F destRect = D2D1::RectF(
					-request.size.width * 0.5f,
					-request.size.height * 0.5f,
					request.size.width * 0.5f,
					request.size.height * 0.5f
				);

				// 화면과 교차 안 하면 스킵
				if (worldX + destRect.right < 0.0f || worldX + destRect.left > application.GetWidth() ||
					worldY + destRect.bottom < 0.0f || worldY + destRect.top > application.GetHeight())
				{
					continue;
				}

				renderTarget->SetTransform(finalTransform);

				// Direct2D의 DrawBitmap 함수를 사용해 텍스처 그리기
				renderTarget->DrawBitmap(
					request.texture->GetBitmap(),
					destRect,
					1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
					request.sourceRect
				);
			}
		}

		renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}

	void RenderManager::RenderTexts(ID2D1HwndRenderTarget* renderTarget, D2D1_MATRIX_3X2_F cameraMatrix)
	{
		for (const auto& request : _textRequestList)
		{
			D2D1_MATRIX_3X2_F finalTransform = request.transformMatrix * cameraMatrix;

			renderTarget->SetTransform(finalTransform);

			_brush->SetColor(request.color);

			renderTarget->DrawText(
				request.text.c_str(),
				request.text.length(),
				request.textFormat,
				request.textRect,
				_brush
			);
		}

		renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}

	void RenderManager::RenderGizmos(ID2D1HwndRenderTarget* renderTarget, D2D1_MATRIX_3X2_F cameraMatrix)
	{
		// 기즈모 요청 처리
		for (const auto& gizmo : _gizmoRequestList)
		{
			D2D1_MATRIX_3X2_F finalTransform = gizmo.transformMatrix * cameraMatrix;

			renderTarget->SetTransform(finalTransform);

			_brush->SetColor(gizmo.color);

			switch (gizmo.type)
			{
			case GizmoType::Circle:
				renderTarget->DrawEllipse(gizmo.ellipse, _brush);
				break;
			case GizmoType::Line:
				renderTarget->DrawLine(gizmo.line.startPoint, gizmo.line.endPoint, _brush);
				break;
			case GizmoType::Box:
				renderTarget->DrawRectangle(gizmo.rect, _brush);
				break;
			default:
				break;
			}
		}
	}

	void RenderManager::AddRenderRequest(const RenderRequest& request)
	{
		_renderRequestList.push_back(request);
	}

	void RenderManager::AddGizmoRequest(const GizmoRequest& request)
	{
		_gizmoRequestList.push_back(request);
	}

	void RenderManager::AddTextRequest(const TextRequest& request)
	{
		_textRequestList.push_back(request);
	}

	void RenderManager::ClearRequests()
	{
		_renderRequestList.clear();
		_textRequestList.clear();
		_gizmoRequestList.clear();
	}
}