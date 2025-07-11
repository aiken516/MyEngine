#pragma once
#include "MyGraphicDevice_DX11.h"

namespace Source::Graphics
{
	class ConstantBuffer : public GpuBuffer
	{
	public:
		ConstantBuffer();
		~ConstantBuffer();

		bool Create(ConstantBufferType type, UINT size, void* data = NULL);

		void SetData(void* data);
		void Bind(ShaderStage stage);
	private:
		UINT _size;
		ConstantBufferType _type;
	};
}
