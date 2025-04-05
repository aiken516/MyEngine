#pragma once
#include "MyComponent.h"
#include "MyAnimation.h"
#include "MyTexture.h"

namespace Source
{
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		//애니메이션은 다른 곳에서 받아서 하는게 나을거 같음, 스프라이트 에디터 등이 있으면 좋을 듯
		void CreateAnimation(const std::wstring& name, 
			Graphics::Texture* spriteSheet,
			Vector2 leftTop, 
			Vector2 offset,
			Vector2 size,
			UINT spriteLength,
			float duration);

		Animation* FindAnimation(const std::wstring& name); 
		void PlayAnimation(const std::wstring& name, bool loop = true);

	private:
		std::map<std::wstring, Animation*> _animations;
		Animation* _currentAnimation;
		bool _isLoop;
	};
}
