#pragma once
#include "MyResource.h"
#include "MyTexture.h"

namespace Source
{
	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			Math::Vector2 leftTop;
			Math::Vector2 offset;
			Math::Vector2 size;
			float duration;

			Sprite() :
				leftTop(Math::Vector2::zero),
				offset(Math::Vector2::zero),
				size(Math::Vector2::zero),
				duration(0.0f)
			{
			}
		};

		Animation();
		~Animation();

		//추후 에디터가 있으면 이용
		virtual HRESULT Load(const std::wstring path) override;

		void Update();

		//애니메이션은 다른 곳에서 받아서 하는게 나을거 같음, 스프라이트 에디터 등이 있으면 좋을 듯
		void CreateAnimation(const std::wstring& name,
			Graphics::Texture* spriteSheet,
			Vector2 leftTop,
			Vector2 offset,
			Vector2 size,
			UINT spriteLength,
			float duration);

		void SetAnimator(class Animator* animator) { _animator = animator; }

		Graphics::Texture* GetSpriteSheet() const { return _spriteSheet; }
		const Sprite& GetCurrentSprite() const { return _animationSheet[_index]; }

		void Reset();
		bool IsComplete() const { return _isComplete; }

	private:
		class Animator* _animator;
		Graphics::Texture* _spriteSheet;
		std::vector<Sprite> _animationSheet;
		int _index;
		float _time;
		bool _isComplete;
	};
}
