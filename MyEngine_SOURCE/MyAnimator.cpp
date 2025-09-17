#include "MyAnimator.h"
#include "MyResources.h"
#include "MyTransform.h"
#include "MyRenderer.h"
#include "MyApplication.h"
#include "MyRenderManager.h"

extern Source::Application application;

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
		for (auto& pair : _animations)
		{
			if (pair.second != nullptr)
			{
				delete pair.second;
				pair.second = nullptr;
			}
		}
		_animations.clear();

		for (auto& pair : _animationEvents)
		{
			if (pair.second != nullptr)
			{
				delete pair.second;
				pair.second = nullptr;
			}
		}
		_animationEvents.clear();
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

	void Animator::Render()
	{
		if (_currentAnimation == nullptr)
		{
			return;
		}

		Graphics::Texture* spriteSheet = _currentAnimation->GetSpriteSheet();
		if (spriteSheet == nullptr)
		{
			return;
		}

		Animation::Sprite currentSprite = _currentAnimation->GetCurrentSprite();
		if (currentSprite.size.x == 0 || currentSprite.size.y == 0)
		{
			return;
		}

		Transform* transform = GetOwner()->GetComponent<Transform>();

		Vector2 position = transform->GetPosition();
		float rotation = transform->GetRotation();
		Vector2 scale = transform->GetScale();

		UINT width = currentSprite.size.x;
		UINT height = currentSprite.size.y;

		if (Renderer::MainCamera != nullptr)
		{
			position = Renderer::MainCamera->CalculatePostion(position);
		}

		float leftTopX = position.x - (width * scale.x * 0.5f);
		float leftTopY = position.y - (height * scale.y * 0.5f);

		float rightBottomX = position.x + (width * scale.x * 0.5f);
		float rightBottomY = position.y + (height * scale.y  * 0.5f);

		if (leftTopX > application.GetWidth() || rightBottomX < 0.0f ||
			leftTopY > application.GetHeight() || rightBottomY < 0.0f)
		{
			return; // 화면 밖에 있으면 렌더링하지 않음
		}

		D2D1_MATRIX_3X2_F rotationMatrix = D2D1::Matrix3x2F::Rotation(
			rotation,
			D2D1::Point2F(position.x - currentSprite.leftTop.x, position.y - currentSprite.leftTop.y)
		);

		D2D1_MATRIX_3X2_F scaleMatrix = D2D1::Matrix3x2F::Scale(
			D2D1::SizeF(scale.x, scale.y),
			D2D1::Point2F(position.x - currentSprite.leftTop.x, position.y - currentSprite.leftTop.y)
		);

		D2D1_MATRIX_3X2_F translationMatrix = D2D1::Matrix3x2F::Translation(
			position.x - currentSprite.leftTop.x, position.y - currentSprite.leftTop.y
		);

		D2D1_MATRIX_3X2_F finalTransform = scaleMatrix * rotationMatrix * translationMatrix;

		RenderRequest request{};
		request.texture = spriteSheet;
		request.sourceRect = D2D1::RectF(
			currentSprite.leftTop.x,
			currentSprite.leftTop.y,
			currentSprite.leftTop.x + currentSprite.size.x,
			currentSprite.leftTop.y + currentSprite.size.y
		);
		request.transformMatrix = finalTransform;

		RenderManager::AddRenderRequest(request);
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

	void Animator::CreateAnimationByFolder(const std::wstring& name, const std::wstring& path, Vector2 offset, float duration)
	{
		/*
		Animation* animation = nullptr;

		animation = FindAnimation(name);
		if (animation != nullptr)
		{
			return;
		}

		std::filesystem::path folderPath(path);
		if (!std::filesystem::exists(folderPath))
		{
			assert(false);
			return;
		}

		std::vector<Graphics::Texture*> imageFiles = {};
		int fileCount = 0;

		for (auto& path : std::filesystem::recursive_directory_iterator(folderPath))
		{
			std::wstring fileName = path.path().filename();
			std::wstring fullName = path.path();

			Graphics::Texture* texture = Resources::Load<Graphics::Texture>(fileName, fullName);
			if (texture != nullptr)
			{
				imageFiles.push_back(texture);
				fileCount++;
			}
		}

		UINT imageWidth = imageFiles[0]->GetWidth();
		UINT imageHeight = imageFiles[0]->GetHeight();

		Graphics::Texture* spriteSheet = Graphics::Texture::Create(name, imageWidth * fileCount, imageHeight);
\
		for (int i = 0; i < imageFiles.size(); i++)
		{
			BitBlt(spriteSheet->GetHdc(), i * imageWidth, 0,
				imageWidth, imageHeight,
				imageFiles[i]->GetHdc(), 0, 0, SRCCOPY);
		}

		CreateAnimation(name, spriteSheet, Vector2::zero, offset,
			Vector2(imageWidth, imageHeight), fileCount, duration);

		*/
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