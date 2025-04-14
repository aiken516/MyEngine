#pragma once
#include "MyComponent.h"
#include "MyAnimation.h"
#include "MyTexture.h"

namespace Source
{
	class Animator : public Component
	{
	public:
		struct AnimationEvnet
		{
			std::wstring name;

			void operator=(std::function<void()> event)
			{
				Event = std::move(event);
			}

			void operator()()
			{
				if (Event != nullptr)
					Event();
			}

			std::function<void()> Event;
		};

		//���߿� ������ �������� ������ �� ������ ��������
		struct AnimationEvents
		{
			AnimationEvnet StartEvent;//���� ��(��������)
			AnimationEvnet CompleteEvent;//������ ��(��������)
			AnimationEvnet EndEvent;//�ٸ� �ִϸ��̼����� �̵� ��
		};

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

		void CreateAnimationByFolder(const std::wstring& name, const std::wstring& path,
			Vector2 offset,
			float duration);

		Animation* FindAnimation(const std::wstring& name); 
		void PlayAnimation(const std::wstring& name, bool loop = true);
		bool IsComplete() { return _currentAnimation->IsComplete(); }

		AnimationEvents* FindAnimationEvent(const std::wstring& name);
		
		//playerAnimator->GetCompleteEvent(L"Attack") = std::bind(&PlayerScript::AttackEffect, playerScript);
		//���� ���·� �̿�, �ּҰ��̱� ������ ������ �� ����
		std::function<void()> GetStartEvent(const std::wstring& name);
		std::function<void()> GetCompleteEvent(const std::wstring& name);
		std::function<void()> GetEndEvent(const std::wstring& name);

	private:
		std::map<std::wstring, Animation*> _animations;
		Animation* _currentAnimation;
		bool _isLoop;

		std::map<std::wstring, AnimationEvents*> _animationEvents;
	};
}
