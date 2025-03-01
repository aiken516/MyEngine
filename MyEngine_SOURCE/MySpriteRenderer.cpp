#include "MySpriteRenderer.h"
#include "MyGameObject.h"
#include "MyTransform.h"

namespace Source
{
	SpriteRenderer::SpriteRenderer()
	{
	}
	SpriteRenderer::~SpriteRenderer()
	{
	}
	void SpriteRenderer::Initialize()
	{
	}
	void SpriteRenderer::Update()
	{
	}
	void SpriteRenderer::LateUpdate()
	{
	}
	void SpriteRenderer::Render(HDC hdc)
	{
		HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
		// �Ķ� �귯�� DC�� ���� �׸��� ��� �귯�� ��ȯ�� ��ȯ
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blueBrush);
		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, redPen);
		SelectObject(hdc, oldBrush);

		Transform* transform = GetOwner()->GetComponent<Transform>();

		Rectangle(hdc, transform->GetX(), transform->GetY(), 
			transform->GetX() + 100, transform->GetY() + 100);

		SelectObject(hdc, oldBrush);
		DeleteObject(blueBrush);
		DeleteObject(redPen);
	}
}