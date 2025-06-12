#pragma once
#include "MyUIBase.h"
#include "MyTexture.h"

namespace Source
{
	class UIImage : public UIBase
	{
	public:
		UIImage();
		~UIImage();

		virtual void OnInitialize() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

		void SetTexture(Graphics::Texture* texture) { _texture = texture; }
	private:
		Graphics::Texture* _texture;
	};
}