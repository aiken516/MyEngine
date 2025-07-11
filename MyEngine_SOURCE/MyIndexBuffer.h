#pragma once
#include "MyGraphicDevice_DX11.h"

namespace Source::Graphics
{
	class IndexBuffer : public GpuBuffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();
		bool Create(const std::vector<UINT>& indices);
		void Bind();
	};
}
