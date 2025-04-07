#include "MyAnimator.h"

namespace Source
{
	Animator::Animator() :
		Component(Enums::ComponentType::Animator),
		_animations{},
		_currentAnimation(nullptr),
		_isLoop(false)
	{
	}

	Animator::~Animator()
	{
	}

	void Animator::Initialize()
	{
	}

	void Animator::Update()
	{
		if (_currentAnimation != nullptr)
		{
			_currentAnimation->Update();
			
			AnimationEvents* events = FindAnimationEvent(_currentAnimation->GetName());
			
			if (_currentAnimation->IsComplete())
			{
				if (events->CompleteEvent.Event != nullptr)
				{
					events->CompleteEvent.Event();
				}

				if (_isLoop)
				{
					_currentAnimation->Reset();
				}
			}
		}
	}

	void Animator::LateUpdate()
	{
	}

	void Animator::Render(HDC hdc)
	{
		if (_currentAnimation != nullptr)
		{
			_currentAnimation->Render(hdc);
		}
	}

	void Animator::CreateAnimation(const std::wstring& name, Graphics::Texture* spriteSheet, 
		Vector2 leftTop, Vector2 offset, Vector2 size, UINT spriteLength, float duration)
	{
		Animation* animation = nullptr;

		animation = FindAnimation(name);
		if (animation != nullptr)
		{
			return;
		}

		animation = new Animation();
		animation->SetName(name);
		animation->CreateAnimation(name, spriteSheet, 
			leftTop, offset, size, spriteLength, duration);

		animation->SetAnimator(this);

		AnimationEvents* events = new AnimationEvents();
		_animationEvents.insert(std::make_pair(name, events));

		_animations.insert(std::make_pair(name, animation));
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		auto iter = _animations.find(name);
		if (iter == _animations.end())
		{
			return nullptr;
		}

		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
		{
			return;
		}

		if (_currentAnimation != nullptr)
		{
			AnimationEvents* currentEvents = FindAnimationEvent(_currentAnimation->GetName());
			if (currentEvents->EndEvent.Event != nullptr)
			{
				currentEvents->EndEvent.Event();
			}
		}

		_currentAnimation = animation;
		_currentAnimation->Reset();
		_isLoop = loop;

		AnimationEvents* nextEvents = FindAnimationEvent(animation->GetName());
		if (nextEvents->StartEvent.Event != nullptr)
		{
			nextEvents->StartEvent.Event();
		}
	}

	Animator::AnimationEvents* Animator::FindAnimationEvent(const std::wstring& name)
	{
		auto iter = _animationEvents.find(name);
		if (iter == _animationEvents.end())
		{
			return nullptr;
		}

		return iter->second;
	}

	std::function<void()> Animator::GetStartEvent(const std::wstring& name)
	{
		AnimationEvents* events = FindAnimationEvent(name);

		return events->StartEvent.Event;
	}

	std::function<void()> Animator::GetCompleteEvent(const std::wstring& name)
	{
		AnimationEvents* events = FindAnimationEvent(name);

		return events->CompleteEvent.Event;
	}

	std::function<void()> Animator::GetEndEvent(const std::wstring& name)
	{
		AnimationEvents* events = FindAnimationEvent(name);

		return events->EndEvent.Event;
	}
}