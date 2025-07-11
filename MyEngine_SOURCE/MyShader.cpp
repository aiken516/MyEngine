#include "MyShader.h"

namespace Source::Graphics
{
	Shader::Shader() : 
		Resource(Enums::ResourceType::Shader)
	{
	}

	Shader::~Shader()
	{
	}

	HRESULT Shader::Load(const std::wstring path)
	{
		int fineNameBeginOffset = path.rfind(L"\\") + 1;
		int fineNameEndOffset = path.length() - fineNameBeginOffset;
		const std::wstring fileName(path.substr(fineNameBeginOffset, fineNameEndOffset));

		if (!Create(ShaderStage::VertexShader, fileName))
		{
			return S_FALSE;
		}
		
		if (!Create(ShaderStage::PixelShader, fileName))
		{
			return S_FALSE;
		}

		return S_OK;
	}

	bool Shader::Create(const ShaderStage shaderStage, const std::wstring& fileName)
	{
		if (shaderStage == ShaderStage::VertexShader)
		{
			CreateVertexShader(fileName);
		}
		else if (shaderStage == ShaderStage::PixelShader)
		{
			CreatePixelShader(fileName);
		}

		return true;
	}

	bool Shader::CreateVertexShader(const std::wstring& fileName)
	{
		if (!GetDevice()->CreateVertexShader(fileName, _vertexBlob.GetAddressOf(), _vertexShader.GetAddressOf()))
		{
			return false;
		}

		return true;
	}

	bool Shader::CreatePixelShader(const std::wstring& fileName)
	{
		if (!GetDevice()->CreatePixelShader(fileName, _pixelBlob.GetAddressOf(), _pixelShader.GetAddressOf()))
		{
			return false;
		}

		return true;
	}

	void Shader::Bind()
	{
		if (_vertexShader != nullptr)
		{
			GetDevice()->BindVertexShader(_vertexShader.Get());
		}

		if (_pixelShader)
		{
			GetDevice()->BindPixelShader(_pixelShader.Get());
		}
	}
}