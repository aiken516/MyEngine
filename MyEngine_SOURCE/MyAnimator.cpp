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
			if (_currentAnimation->IsComplete() && _isLoop)
			{
				_currentAnimation->Reset();
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
		animation->CreateAnimation(name, spriteSheet, 
			leftTop, offset, size, spriteLength, duration);

		animation->SetAnimator(this);
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

		_currentAnimation = animation;
		_currentAnimation->Reset();
		_isLoop = loop;
	}
}