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

	void Animation::Render(HDC hdc)
	{
		if (_spriteSheet == nullptr)
		{
			return;
		}

		GameObject* gameObject = _animator->GetOwner();
		Transform* transform = gameObject->GetComponent<Transform>();
		Vector2 position = transform->GetPosition();
		float rotation = transform->GetRotation();
		Vector2 scale = transform->GetScale();

		if (Renderer::MainCamera != nullptr)
		{
			position = Renderer::MainCamera->CalculatePostion(position);
		}

		Sprite currentSprite = _animationSheet[_index];
		
		// 애니메이션이 중앙이 되도록 보정
		float leftTopX = position.x - (currentSprite.size.x * scale.x * 0.5f) + currentSprite.offset.x;
		float leftTopY = position.y - (currentSprite.size.y * scale.y * 0.5f) + currentSprite.offset.y;

		float rightBottomX = position.x + (currentSprite.size.x * scale.x * 0.5f) + currentSprite.offset.x;
		float rightBottomY = position.y + (currentSprite.size.y * scale.y * 0.5f) + currentSprite.offset.y;

		if (leftTopX > application.GetWidth() || rightBottomX < 0.0f ||
			leftTopY > application.GetHeight() || rightBottomY < 0.0f)
		{
			return; // 화면 밖에 있는 경우 컬링
		}

		Graphics::Texture::TextureType type = _spriteSheet->GetTextureType();
		
		if (type == Graphics::Texture::TextureType::Bmp)
		{
			if (_spriteSheet->HasAlpha())
			{
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 255; // 0(완전 투명) ~ 255(완전 불투명)

				AlphaBlend(hdc, 
					leftTopX,
					leftTopY,
					rightBottomX - leftTopX,
					rightBottomY - leftTopY,
					_spriteSheet->GetHdc(),
					currentSprite.leftTop.x,
					currentSprite.leftTop.y,
					currentSprite.size.x,
					currentSprite.size.y,
					func);//마젠타를 보통 투명색으로함
			}
			else
			{
				TransparentBlt(hdc,
					leftTopX,
					leftTopY,
					rightBottomX - leftTopX,
					rightBottomY - leftTopY,
					_spriteSheet->GetHdc(),
					currentSprite.leftTop.x,
					currentSprite.leftTop.y,
					currentSprite.size.x,
					currentSprite.size.y,
					RGB(255, 0, 255));
			}

			//가운데 위치 TEST용
			Rectangle(hdc, position.x, position.y, position.x + 5, position.y + 5);
		}
		else if (type == Graphics::Texture::TextureType::Png)
		{
			//내가 원하는 픽셀을 투명화할 때
			Gdiplus::ImageAttributes imageAttributes = {};
			//투명화시킬 색 범위
			imageAttributes.SetColorKey(Gdiplus::Color(100,100,100), Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphcis(hdc);
			graphcis.TranslateTransform(position.x, position.y);
			graphcis.RotateTransform(transform->GetRotation());
			graphcis.TranslateTransform(-position.x, -position.y);

			graphcis.DrawImage(_spriteSheet->GetSprite(),
				Gdiplus::Rect(
					leftTopX,
					leftTopY,
					rightBottomX - leftTopX,
					rightBottomY - leftTopY
				),
				currentSprite.leftTop.x,
				currentSprite.leftTop.y, 
				currentSprite.size.x,
				currentSprite.size.y,
				Gdiplus::UnitPixel,
				nullptr
			);
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