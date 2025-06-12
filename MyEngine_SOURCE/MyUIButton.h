#pragma once
#include "MyUIBase.h"
#include "MyTexture.h"

namespace Source
{
	class UIButton : public UIBase
	{
	public:
		UIButton();
		~UIButton();

		virtual void OnInitialize() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;
		
		virtual void OnClick();

		void SetTexture(Graphics::Texture* texture) { _texture = texture; }
		void SetOnClickEvent(const Event& event) { _onClickEvent = event; }
	private:
		Graphics::Texture* _texture;
		Event _onClickEvent;
	};
}