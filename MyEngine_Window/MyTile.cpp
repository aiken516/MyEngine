#include "MyTile.h"
#include "MyTransform.h"
#include "MyTilemapRenderer.h"

namespace Client
{
	void Tile::Initialize()
	{
		GameObject::Initialize();
	}

	void Tile::Update()
	{
		GameObject::Update();
	}

	void Tile::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Tile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	/// <summary>
	/// 인덱스로 타일의 위치를 설정
	/// </summary>
	/// <param name="x">인덱스 x</param>
	/// <param name="y">인덱스 y</param>
	void Tile::SetPositionByIndex(int x, int y)
	{
		Transform* transform = GetComponent<Transform>();
		Vector2 position;
		position.x = x * TilemapRenderer::TileSize.x;
		position.y = y * TilemapRenderer::TileSize.y;
		transform->SetPosition(position);
	}
}