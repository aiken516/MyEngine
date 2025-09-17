#include "MyRenderManager.h"
#include "MyRenderer.h"
#include "MyApplication.h"

#include <algorithm>

extern Source::Application application;

namespace Source
{
	std::vector<RenderRequest> RenderManager::_renderRequestList = {};
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

		// 텍스처 포인터 주소값 기준 정렬 로직은 유지
		std::sort(_renderRequestList.begin(), _renderRequestList.end(),
			[](const RenderRequest& a, const RenderRequest& b) {
				return a.texture < b.texture;
			});

		for (const auto& request : _renderRequestList)
		{
			if (request.texture != nullptr && request.texture->GetBitmap())
			{
				// Direct2D의 DrawBitmap 함수를 사용해 텍스처 그리기
				renderTarget->SetTransform(request.transformMatrix);

				renderTarget->DrawBitmap(
					request.texture->GetBitmap(),
					request.sourceRect,
					1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
					request.sourceRect
				);
			}
		}

		renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		
		// 기즈모 요청 처리
		for (const auto& gizmo : _gizmoRequestList)
		{
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

	void RenderManager::ClearRequests()
	{
		_renderRequestList.clear();
		_gizmoRequestList.clear();
	}
}