#include "MyTexture.h"
#include "MyApplication.h"
#include "MyResources.h"

// �ش� ���������� �������� �˸��� Ű���� extern
extern Source::Application application;

namespace Source::Graphics	
{
	Texture::Texture() :
		Resource(Enums::ResourceType::Texture),
		_hasAlpha(false),
		_textureType(TextureType::NONE),
		_width(0),
		_height(0)
	{
	}
	
	Texture::~Texture()
	{
	}

	Texture* Texture::Create(const std::wstring& name, UINT width, UINT height)
	{
		Texture* texture = Resources::Find<Texture>(name);
		if (texture != nullptr)
		{
			return texture;
		}

		texture = new Texture();
		texture->SetName(name);
		texture->SetWidth(width);
		texture->SetHeight(height);

		return texture;
	}

	HRESULT Texture::Load(const std::wstring path)
	{
		//���� Ȯ���� �޾ƿ���
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

		//�̹����� bmp�� ��

		return S_OK;
	}
}