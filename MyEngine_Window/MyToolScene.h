#pragma once
#include "..\\MyEngine_SOURCE\\MyScene.h"
#include "MyTile.h"
using namespace Source;

LRESULT CALLBACK ToolWindowProcedure(HWND, UINT, WPARAM, LPARAM);

namespace Client
{
	class ToolScene : public Scene
	{
	public:
		ToolScene();
		~ToolScene();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;

		void Save();
		void Load();
	private:
		std::vector<Tile*> _tiles;
	};
}
