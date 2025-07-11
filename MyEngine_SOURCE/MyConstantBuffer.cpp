#include "MyConstantBuffer.h"

namespace Source::Graphics
{
	ConstantBuffer::ConstantBuffer()
	{
	}

	ConstantBuffer::~ConstantBuffer()
	{
	}

	bool ConstantBuffer::Create(ConstantBufferType type, UINT size, void* data)
	{
		_type = type;
		_size = size;
		Description.ByteWidth = size;
		Description.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		Description.Usage = D3D11_USAGE_DYNAMIC;
		Description.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sub = {};
		sub.pSysMem = data;

		bool isSucces = false;
		if (data == NULL)
		{
			isSucces = GetDevice()->CreateBuffer(&Description, nullptr, Buffer.GetAddressOf());
		}
		else
		{
			isSucces = GetDevice()->CreateBuffer(&Description, &sub, Buffer.GetAddressOf());
		}

		if (!isSucces)
		{
			assert(NULL, "Create constant buffer failed!");
		}

		return true;
	}

	void ConstantBuffer::SetData(void* data)
	{
	}

	void ConstantBuffer::Bind(ShaderStage stage)
	{
	}
}