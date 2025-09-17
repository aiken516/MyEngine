#pragma once
#include "MySpriteRenderer.h"

namespace Source
{
	struct SpriteRenderRequest
	{
		Graphics::Texture* texture;
		D2D1_MATRIX_3X2_F transformMatrix;
		D2D1_RECT_F sourceRect;
		D2D1_SIZE_F size;
	};

	struct TextRenderRequest
	{
		std::wstring text;
		D2D1_RECT_F textRect;
		D2D1_MATRIX_3X2_F transformMatrix;
		D2D1_COLOR_F color;
		IDWriteTextFormat* textFormat;
	};

	enum class GizmoType
	{
		Circle,
		Line,
		Box
	};

	struct GizmoRenderRequest
	{
		GizmoType type;
		D2D1_MATRIX_3X2_F transformMatrix;
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

		static void AddSpriteRequest(const SpriteRenderRequest& request);
		static void AddGizmoRequest(const GizmoRenderRequest& request);
		static void AddTextRequest(const TextRenderRequest& request);
		static void ClearRequests();
	private:
		static void RenderSprites(ID2D1HwndRenderTarget* renderTarget, D2D1_MATRIX_3X2_F cameraMatrix);
		static void RenderTexts(ID2D1HwndRenderTarget* renderTarget, D2D1_MATRIX_3X2_F cameraMatrix);
		static void RenderGizmos(ID2D1HwndRenderTarget* renderTarget, D2D1_MATRIX_3X2_F cameraMatrix);

		static ID2D1SolidColorBrush* _brush;

		static std::map<ID2D1Bitmap*, std::vector<SpriteRenderRequest>> _spriteRequestBatches;
		static std::vector<TextRenderRequest> _textRequestList;
		static std::vector<GizmoRenderRequest> _gizmoRequestList;
	};
}