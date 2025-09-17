#include "MyRenderManager.h"
#include "MyRenderer.h"
#include "MyApplication.h"

#include <algorithm>

extern Source::Application application;

namespace Source
{
	std::vector<RenderRequest> RenderManager::_renderRequestList = {};

	void RenderManager::Initialize()
	{
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

		// �ؽ�ó ������ �ּҰ� ���� ���� ������ ����
		std::sort(_renderRequestList.begin(), _renderRequestList.end(),
			[](const RenderRequest& a, const RenderRequest& b) {
				return a.texture < b.texture;
			});

		for (const auto& request : _renderRequestList)
		{
			if (request.texture != nullptr && request.texture->GetBitmap())
			{
				// Direct2D�� DrawBitmap �Լ��� ����� �ؽ�ó �׸���
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
	}

	void RenderManager::AddRenderRequest(const RenderRequest& request)
	{
		_renderRequestList.push_back(request);
	}

	void RenderManager::ClearRenderRequests()
	{
		_renderRequestList.clear();
	}
}