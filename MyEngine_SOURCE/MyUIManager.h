#pragma once

#include "CommonInclude.h"
#include "MyUIBase.h"

namespace Source
{
	using namespace Enums;

	class UIManager
	{
	public:
		UIManager();
		~UIManager();
		static void Initialize();
		static void OnLoad(UIType type);
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);
		static void OnComplete(UIBase* addUI);
		static void OnFail();
		static void Release();

		static void Push(UIType type);
		static void Pop(UIType type);
	private:
		static std::unordered_map<UIType, UIBase*> _uis;
		static std::stack<UIBase*> _uiBaseStack;
		static std::queue<UIType> _requestUIQueue;
		static UIBase* _activeUI;
	};
}
