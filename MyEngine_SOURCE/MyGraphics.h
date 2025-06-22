#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "CommonInclude.h"

namespace Source::Graphics
{
	enum class ShaderStage
	{
		VS,	// Vertex Shader
		HS,	// Hull Shader
		DS,	// Domain Shader
		GS,	// Geometry Shader
		PS,	// Pixel Shader
		CS,	// Compute Shader
		All,
		End,
	};

	enum class CBType
	{
		Transform,
		End,
	};
}