#include "MyToolScene.h"
#include "MyObject.h"
#include "MyTile.h"
#include "MyTilemapRenderer.h"
#include "MyResources.h"
#include "MyCamera.h"
#include "MyRenderer.h"
#include "MyApplication.h"
#include "MyInput.h"
#include "MyCameraController.h"

#include "MySpriteRenderer.h"

extern Source::Application application;

namespace Client
{
	ToolScene::ToolScene()
	{
	}

	ToolScene::~ToolScene()
	{
	}

	void ToolScene::Initialize()
	{
		// -------------------- 카메라 --------------------
		GameObject* camera = Object::Instantiate<GameObject>(
			Enums::LayerType::None, Vector2(application.GetWidth() / 2, application.GetHeight() / 2));
		Camera* cameraComponent = camera->AddComponent<Camera>();
		camera->AddComponent<CameraController>();

		Renderer::MainCamera = cameraComponent;

		// -------------------- 타일맵 --------------------

		Tile* tile = Object::Instantiate<Tile>(Enums::LayerType::Background, Vector2(0.0f, 0.0f));
		TilemapRenderer* tilemapRenderer = tile->AddComponent<TilemapRenderer>();
		//SpriteRenderer* tilemapRenderer = tile->AddComponent<SpriteRenderer>();

		tilemapRenderer->SetTexture(Resources::Find<Graphics::Texture>(L"SpringFloor"));

		Scene::Initialize();
	}

	void ToolScene::Update()
	{
		Scene::Update();
	}

	void ToolScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (Input::GetKeyDown(KeyCode::LBUTTON))
		{
			Vector2 mouseInputPosition = Input::GetMousePosition();
			Vector2 mousePosition = Renderer::MainCamera->CalculateMousePostion(mouseInputPosition);

			if (mousePosition.x >= 0.0f && mousePosition.y >= 0.0f)
			{
				int indexX = mousePosition.x / TilemapRenderer::TileSize.x;
				int indexY = mousePosition.y / TilemapRenderer::TileSize.y;

				if (TilemapRenderer::SelectedIndex.x == -1.0f)
				{
				}
				else
				{
					Tile* tile = Object::Instantiate<Tile>(LayerType::Tile);
					TilemapRenderer* tilemapRenderer = tile->AddComponent<TilemapRenderer>();
					tilemapRenderer->SetTexture(Resources::Find<Graphics::Texture>(L"SpringFloor"));
					tilemapRenderer->SetIndex(TilemapRenderer::SelectedIndex);

					tile->SetPositionByIndex(indexX, indexY);
					_tiles.push_back(tile);
				}
			}
		}
		
		if (Input::GetKeyDown(KeyCode::S))
		{
			Save();
		}
		
		if (Input::GetKeyDown(KeyCode::L))
		{
			Load();
		}
	}

	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		Vector2 tileSize = TilemapRenderer::TileSize;
		Vector2 resolution = Vector2(application.GetWidth(), application.GetHeight());

		for (size_t i = 0; i < resolution.x; i += tileSize.x)
		{
			Vector2 position = Renderer::MainCamera->CalculatePostion(Vector2(i, 0.0f));

			MoveToEx(hdc, position.x, 0, NULL);
			LineTo(hdc, position.x, resolution.y);
		}

		for (size_t i = 0; i < resolution.y; i += tileSize.y)
		{
			Vector2 position = Renderer::MainCamera->CalculatePostion(Vector2(0.0f, i));

			MoveToEx(hdc, 0, position.y, NULL);
			LineTo(hdc, resolution.x, position.y);
		}
	}

	void ToolScene::OnEnter()
	{
		Scene::OnEnter();
	}

	void ToolScene::OnExit()
	{
		Scene::OnExit();
	}

	void ToolScene::Save()
	{
		// open a file name
		OPENFILENAME openFileName = {};

		wchar_t filePath[256] = {};

		ZeroMemory(&openFileName, sizeof(openFileName));
		openFileName.lStructSize = sizeof(openFileName);
		openFileName.hwndOwner = NULL;
		openFileName.lpstrFile = filePath;
		openFileName.lpstrFile[0] = '\0';
		openFileName.nMaxFile = 256;
		openFileName.lpstrFilter = L"Tile\0*.tilemap\0";
		openFileName.nFilterIndex = 1;
		openFileName.lpstrFileTitle = NULL;
		openFileName.nMaxFileTitle = 0;
		openFileName.lpstrInitialDir = NULL;
		openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&openFileName))
		{
			return;
		}

		FILE* opendFile = nullptr;
		_wfopen_s(&opendFile, filePath, L"wb");

		for (Tile* tile : _tiles)
		{
			TilemapRenderer* tilemapRenderer = tile->GetComponent<TilemapRenderer>();
			Transform* tileTransform = tile->GetComponent<Transform>();

			Vector2 sourceIndex = tilemapRenderer->GetIndex();
			Vector2 position = tileTransform->GetPosition();

			int x = sourceIndex.x;
			fwrite(&x, sizeof(int), 1, opendFile);
			int y = sourceIndex.y;
			fwrite(&y, sizeof(int), 1, opendFile);

			x = position.x;
			fwrite(&x, sizeof(int), 1, opendFile);
			y = position.y;
			fwrite(&y, sizeof(int), 1, opendFile);
		}

		fclose(opendFile);
	}

	void ToolScene::Load()
	{
		OPENFILENAME openFileName = {};

		wchar_t filePath[256] = {};

		ZeroMemory(&openFileName, sizeof(openFileName));
		openFileName.lStructSize = sizeof(openFileName);
		openFileName.hwndOwner = NULL;
		openFileName.lpstrFile = filePath;
		openFileName.lpstrFile[0] = '\0';
		openFileName.nMaxFile = 256;
		openFileName.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
		openFileName.nFilterIndex = 1;
		openFileName.lpstrFileTitle = NULL;
		openFileName.nMaxFileTitle = 0;
		openFileName.lpstrInitialDir = NULL;
		openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetOpenFileName(&openFileName))
		{
			return;
		}

		FILE* opendFile = nullptr;
		_wfopen_s(&opendFile, filePath, L"rb");

		while (true)
		{
			int indexX = 0;
			int indexY = 0;

			int positionX = 0;
			int positionY = 0;

			if (fread(&indexX, sizeof(int), 1, opendFile) == NULL)
				break;
			if (fread(&indexY, sizeof(int), 1, opendFile) == NULL)
				break;
			if (fread(&positionX, sizeof(int), 1, opendFile) == NULL)
				break;
			if (fread(&positionY, sizeof(int), 1, opendFile) == NULL)
				break;

			Tile* tile = Object::Instantiate<Tile>(LayerType::Tile, Vector2(positionX, positionY));
			TilemapRenderer* tilemapRenderer = tile->AddComponent<TilemapRenderer>();
			tilemapRenderer->SetTexture(Resources::Find<Graphics::Texture>(L"SpringFloor"));
			tilemapRenderer->SetIndex(Vector2(indexX, indexY));

			//tile->SetPositionByIndex(indexX, indexY);
			_tiles.push_back(tile);
		}

		fclose(opendFile);
	}
}

LRESULT CALLBACK ToolWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		POINT mousePos = { };
		GetCursorPos(&mousePos);
		ScreenToClient(hWnd, &mousePos);

		Math::Vector2 mousePosition;
		mousePosition.x = mousePos.x;
		mousePosition.y = mousePos.y;

		int idxX = mousePosition.x / Source::TilemapRenderer::OriginTileSize.x;
		int idxY = mousePosition.y / Source::TilemapRenderer::OriginTileSize.y;

		Source::TilemapRenderer::SelectedIndex = Vector2(idxX, idxY);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// ========================= 무조건 여기서 제거하기 =========================
		Source::Graphics::Texture* texture = Source::Resources::Find<Source::Graphics::Texture>(L"SpringFloor");
		TransparentBlt(hdc,
			0,
			0,
			texture->GetWidth(),
			texture->GetHeight(),
			texture->GetHdc(),
			0, 0,
			texture->GetWidth(),
			texture->GetHeight(),
			RGB(255, 0, 255));//마젠타
		// ========================= 무조건 여기서 제거하기 =========================

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOVE:
	{

	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}