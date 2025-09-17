#pragma once
#include "MySpriteRenderer.h"

namespace Source
{
	struct RenderRequest
	{
		Graphics::Texture* texture;
		D2D1_MATRIX_3X2_F transformMatrix;
		D2D1_RECT_F sourceRect;
	};

	enum class GizmoType
	{
		Circle,
		Line,
		Box
	};

	struct GizmoRequest
	{
		GizmoType type;
		D2D1_COLOR_F color;

		union
		{
			D2D1_ELLIPSE ellipse;
			struct {
				D2D1_POINT_2F startPoint;
				D2D1_POINT_2F endPoint;
			} line;
			D2D1_RECT_F rect;
		};
	};

	class RenderManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(ID2D1HwndRenderTarget* renderTarget);

		static void AddRenderRequest(const RenderRequest& request);
		static void AddGizmoRequest(const GizmoRequest& request);
		static void ClearRequests();
	private:
		static ID2D1SolidColorBrush* _brush;

		static std::vector<RenderRequest> _renderRequestList;
		static std::vector<GizmoRequest> _gizmoRequestList;
	};
}