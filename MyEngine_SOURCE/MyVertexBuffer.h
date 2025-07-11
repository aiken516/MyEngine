#pragma once
#include "MyGraphicDevice_DX11.h"

namespace Source::Graphics
{
	class VertexBuffer : public GpuBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();
		bool Create(const std::vector<Vertex>& vertexes);
		void Bind();
	};
}