#include "MyUIManager.h"
#include "MyUIImage.h"
#include "MyUIButton.h"

namespace Source
{
	std::unordered_map<UIType, UIBase*> UIManager::_uis = {};
	std::stack<UIBase*> UIManager::_uiBaseStack = {};
	std::queue<UIType> UIManager::_requestUIQueue = {};
	UIBase* UIManager::_activeUI = nullptr;

	UIManager::UIManager()
	{
	}

	UIManager::~UIManager()
	{
	}

	void UIManager::Initialize()
	{
		UIImage* image = new UIImage();
		_uis.insert(std::make_pair(UIType::Image, image));

		UIButton* button = new UIButton();
		_uis.insert(std::make_pair(UIType::Button, button));
	}

	void UIManager::OnLoad(UIType type)
	{
		std::unordered_map<UIType, UIBase*>::iterator iter = _uis.find(type);
		if (iter != _uis.end())
		{
			OnComplete(iter->second);
		}
		else
		{
			OnFail();
		}
	}

	void UIManager::Update()
	{
		std::stack<UIBase*> uiBaseStack = _uiBaseStack;
		while (!uiBaseStack.empty())
		{
			UIBase* uiBase = uiBaseStack.top();
			if (uiBase != nullptr)
			{
				uiBase->Update();
				uiBaseStack.pop();
			}
		}

		if (_requestUIQueue.size() > 0)
		{
			UIType requestUI = _requestUIQueue.front();
			_requestUIQueue.pop();
			OnLoad(requestUI);
		}
	}

	void UIManager::LateUpdate()
	{
		std::stack<UIBase*> uiBaseStack = _uiBaseStack;
		while (!uiBaseStack.empty())
		{
			UIBase* uiBase = uiBaseStack.top();
			if (uiBase != nullptr)
			{
				uiBase->LateUpdate();
				uiBaseStack.pop();
			}
		}
	}

	void UIManager::Render(HDC hdc)
	{
		std::stack<UIBase*> uiBaseStack = _uiBaseStack;
		while (!uiBaseStack.empty())
		{
			UIBase* uiBase = uiBaseStack.top();
			if (uiBase != nullptr)
			{
				uiBase->Render(hdc);
				uiBaseStack.pop();
			}
		}
	}

	void UIManager::OnComplete(UIBase* addUI)
	{
		if (addUI == nullptr)
		{
			return;
		}

		addUI->Initialize();
		addUI->Active();
		addUI->Update();

		// 만약에 현재 추가된 ui가 전체화면이라면
		// 전체화면인 ui 말고 나머지를 전부 비활성화
		if (addUI->IsFullScreen())
		{
			std::stack<UIBase*> uiBaseStack = _uiBaseStack;
			while (!uiBaseStack.empty())
			{
				UIBase* uiBase = uiBaseStack.top();
				uiBaseStack.pop();
				if (uiBase)
				{
					uiBase->InActive();
				}
			}
		}

		_uiBaseStack.push(addUI);
		_activeUI = nullptr;
	}

	void UIManager::OnFail()
	{
		_activeUI = nullptr;
	}

	void UIManager::Release()
	{
		for (auto& iter : _uis)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	void UIManager::Push(UIType type)
	{
		_requestUIQueue.push(type);
	}

	void UIManager::Pop(UIType type)
	{
		if (_uiBaseStack.size() <= 0)
		{
			return;
		}

		std::stack<UIBase*> tempStack;

		UIBase* uiBase = nullptr;
		while (_uiBaseStack.size() > 0)
		{
			uiBase = _uiBaseStack.top();
			_uiBaseStack.pop();

			if (uiBase->GetType() != type)
			{
				tempStack.push(uiBase);
				continue;
			}

			if (uiBase->IsFullScreen())
			{
				std::stack<UIBase*> uiBaseStack = _uiBaseStack;
				while (!uiBaseStack.empty())
				{
					UIBase* uiBase = uiBaseStack.top();
					uiBaseStack.pop();
					if (uiBase)
					{
						uiBase->Active();
						break;
					}
				}
			}

			uiBase->Clear();
		}

		while (tempStack.size() > 0)
		{
			uiBase = tempStack.top();
			tempStack.pop();
			_uiBaseStack.push(uiBase);
		}
	}
}