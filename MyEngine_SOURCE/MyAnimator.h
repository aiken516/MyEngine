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

		//�ִϸ��̼��� �ٸ� ������ �޾Ƽ� �ϴ°� ������ ����, ��������Ʈ ������ ���� ������ ���� ��
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
