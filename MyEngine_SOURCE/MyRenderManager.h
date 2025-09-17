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

	class RenderManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(ID2D1HwndRenderTarget* renderTarget);

		static void AddRenderRequest(const RenderRequest& request);
		static void ClearRenderRequests();
	private:
		static 	std::vector<RenderRequest> _renderRequestList;

	};
}