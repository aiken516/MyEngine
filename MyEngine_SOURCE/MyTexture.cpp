#include "MyTexture.h"
#include "MyApplication.h"
#include "MyResources.h"

// 해당 전역변수가 존재함을 알리는 키워드 extern
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
		//파일 확장자 받아오기
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

		//이미지가 bmp일 때

		return S_OK;
	}
}