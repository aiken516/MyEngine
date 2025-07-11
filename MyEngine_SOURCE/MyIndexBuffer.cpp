#include "MyIndexBuffer.h"

namespace Source::Graphics
{
	IndexBuffer::IndexBuffer()
	{
	}

	IndexBuffer::~IndexBuffer()
	{
	}

	bool IndexBuffer::Create(const std::vector<UINT>& indices)
	{
		Description.ByteWidth = sizeof(UINT) * indices.size();
		Description.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		Description.Usage = D3D11_USAGE_DEFAULT;
		Description.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sub = {};
		sub.pSysMem = indices.data();

		if (!GetDevice()->CreateBuffer(&Description, &sub, Buffer.GetAddressOf()))
		{
			assert(NULL && "indices buffer create fail");
		}

		return true;
	}

	void IndexBuffer::Bind()
	{
		GetDevice()->BindIndexBuffer(Buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}
}