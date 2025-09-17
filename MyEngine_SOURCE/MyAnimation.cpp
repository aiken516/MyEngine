#include "MyAnimation.h"
#include "MyAnimator.h"
#include "MyTime.h"
#include "MyGameObject.h"
#include "MyTransform.h"
#include "MyRenderer.h"
#include "MyApplication.h"

extern Source::Application application;

namespace Source
{
	Animation::Animation() :
		Resource(Enums::ResourceType::Animation),
		_animator(nullptr),
		_spriteSheet(nullptr),
		_animationSheet{},
		_index(-1),
		_time(0.0f),
		_isComplete(false)
	{
	}

	Animation::~Animation()
	{
	}

	HRESULT Animation::Load(const std::wstring path)
	{
		return E_NOTIMPL;
	}

	void Animation::Update()
	{
		if (_isComplete)
		{
			return;
		}

		_time += Time::DeltaTime();

		if (_time >= _animationSheet[_index].duration)
		{
			_time = 0.0f;

			if (_index < _animationSheet.size() - 1)
			{
				_index++;
			}
			else
			{
				_isComplete = true;
			}
		}
	}

	void Animation::CreateAnimation(const std::wstring& name, Graphics::Texture* spriteSheet, 
		Vector2 leftTop, Vector2 offset, Vector2 size, UINT spriteLength, float duration)
	{
		_spriteSheet = spriteSheet;
		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + (size.x * i);
			sprite.leftTop.y = leftTop.y;
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			_animationSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
		_time = 0.0f;
		_index = 0;
		_isComplete = false;
	}
}