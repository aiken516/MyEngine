#pragma once
#include "MyEntity.h"
#include "MyComponent.h"
#include "MyTexture.h"

namespace Source
{
	class TilemapRenderer : public Component
	{
	public:
		TilemapRenderer();
		~TilemapRenderer();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;

		void SetTexture(Graphics::Texture* texture) { _texture = texture; }
		void SetSize(Vector2 size) { _size = size; }
	
	// ===== 추후 수정 필요 =====
		void SetIndex(Vector2 index) { _index = index; }
		Vector2 GetIndex() const { return _index; }
	public:
		static Vector2 TileSize;
		static Vector2 OriginTileSize;
		static Vector2 SelectedIndex;
	// ========================
	private:
		Graphics::Texture* _texture;
		Vector2 _size;
		Vector2 _index;
		Vector2 _tileSize;
	};
}