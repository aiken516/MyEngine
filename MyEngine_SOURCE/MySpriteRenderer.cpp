#include "MySpriteRenderer.h"
#include "MyGameObject.h"
#include "MyTransform.h"
#include "MyTexture.h"
#include "MyRenderer.h"

#include <windows.h>  // �⺻ Windows API ���
#include <Shlwapi.h>  // PathFileExists()�� ����� ���
#include <iostream>

#pragma comment(lib, "Shlwapi.lib")  // ���̺귯�� ��ũ

namespace Source
{
	SpriteRenderer::SpriteRenderer() :
		Component(Enums::ComponentType::Renderer),
		_texture(nullptr),
		_size(Vector2::One)
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

	void SpriteRenderer::Render()
	{
		if (_texture == nullptr)
		{
			assert(false);
		}

	}
}