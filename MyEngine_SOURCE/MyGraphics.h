#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "CommonInclude.h"

namespace Source::Graphics
{
	struct Vertex
	{
		Math::Vector3 Position;
		Math::Vector4 Color;
	};

	enum class ShaderStage
	{
		VertexShader,	// Vertex Shader
		HullShader,	// Hull Shader
		DomainShader,	// Domain Shader
		GeometryShader,	// Geometry Shader
		PixelShader,	// Pixel Shader
		ComputeShader,	// Compute Shader
		All,
		End,
	};

	enum class ConstantBufferType
	{
		Transform,
		None,
		End,
	};

	struct GpuBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> Buffer = nullptr;
		D3D11_BUFFER_DESC Description = {};

		GpuBuffer() = default;
		virtual ~GpuBuffer() = default;
	};
}