#pragma once
#include "MyEntity.h"
#include "MyComponent.h"
#include "MyTexture.h"

namespace Source
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;

		void SetTexture(Graphics::Texture* texture) { _texture = texture; }
		void SetSize(Math::Vector2 size) { _size = size; }

	private:
		Graphics::Texture* _texture;
		Math::Vector2 _size;
	};
}
