#include "MyVertexBuffer.h"
#include "MyGraphicDevice_DX11.h"

namespace Source::Graphics
{
	VertexBuffer::VertexBuffer()
	{
	}

	VertexBuffer::~VertexBuffer()
	{
	}

	bool VertexBuffer::Create(const std::vector<Vertex>& vertexes)
	{
		Description.ByteWidth = sizeof(Vertex) * (UINT)vertexes.size();
		Description.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		Description.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		Description.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sub = { };
		sub.pSysMem = vertexes.data();

		if (!GetDevice()->CreateBuffer(&Description, &sub, Buffer.GetAddressOf()))
		{
			assert(NULL, "Create vertex buffer failed");
		}
		
		return true;
	}

	void VertexBuffer::Bind()
	{
		UINT offset = 0;
		UINT vectexSize = sizeof(Vertex);
		GetDevice()->BindVertexBuffer(0, 1, Buffer.GetAddressOf(), &vectexSize, &offset);
	}
}	