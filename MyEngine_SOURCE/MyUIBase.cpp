#include "MyUIBase.h"

namespace Source
{
	UIBase::UIBase(UIType type) :
		_type(type),
		_isFullScreen(false),
		_isActive(false)
	{
	}

	UIBase::~UIBase()
	{
	}

	/// <summary>
	/// UI �ε� �� ȣ��Ǵ� �ʱ�ȭ �Լ�
	/// </summary>
	void UIBase::Initialize()
	{
		OnInitialize();
	}

	/// <summary>
	/// UI Ȱ��ȭ �� ȣ��Ǵ� �Լ�
	/// </summary>
	void UIBase::Active()
	{
		_isActive = true;
		OnActive();
	}

	/// <summary>
	/// UI ��Ȱ��ȭ �� ȣ��Ǵ� �Լ�
	/// </summary>
	void UIBase::InActive()
	{
		_isActive = false;
		OnInActive();
	}

	void UIBase::Update()
	{
		if (_isActive)
		{
			OnUpdate();
		}
	}

	void UIBase::LateUpdate()
	{
		if (_isActive)
		{
			OnLateUpdate();
		}
	}

	void UIBase::Render(HDC hdc)
	{
		if (_isActive)
		{
			OnRender(hdc);
		}
	}

	/// <summary>
	/// UI�� ����� �� ȣ��Ǵ� �Լ�
	/// </summary>
	void UIBase::Clear()
	{
		OnClear();
	}

	void UIBase::OnInitialize()
	{
	}

	void UIBase::OnActive()
	{
	}

	void UIBase::OnInActive()
	{
	}

	void UIBase::OnUpdate()
	{
	}

	void UIBase::OnLateUpdate()
	{
	}

	void UIBase::OnRender(HDC hdc)
	{
	}

	void UIBase::OnClear()
	{
	}
}