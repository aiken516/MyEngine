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

		//나중에 프레임 각각으로 수정할 수 있으면 좋을듯함
		struct AnimationEvents
		{
			AnimationEvnet StartEvent;//시작 시(루프마다)
			AnimationEvnet CompleteEvent;//끝났을 때(루프마다)
			AnimationEvnet EndEvent;//다른 애니메이션으로 이동 시
		};

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

		void CreateAnimationByFolder(const std::wstring& name, const std::wstring& path,
			Vector2 offset,
			float duration);

		Animation* FindAnimation(const std::wstring& name); 
		void PlayAnimation(const std::wstring& name, bool loop = true);
		bool IsComplete() { return _currentAnimation->IsComplete(); }

		AnimationEvents* FindAnimationEvent(const std::wstring& name);
		
		//playerAnimator->GetCompleteEvent(L"Attack") = std::bind(&PlayerScript::AttackEffect, playerScript);
		//위의 형태로 이용, 주소값이기 때문에 대입할 수 있음
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
