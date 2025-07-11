#pragma once
#include "MyCamera.h"
#include "MyGraphicDevice_DX11.h"
#include "MyVertexBuffer.h"
#include "MyIndexBuffer.h"
#include "MyConstantBuffer.h"

using namespace Source::Math;
using namespace Source::Graphics;

namespace Source::Renderer
{
	extern Camera* MainCamera;

	extern std::vector<Vertex> Vertexes;
	extern std::vector<UINT> Indices;

	extern Graphics::VertexBuffer VertexBuffer;
	extern Graphics::IndexBuffer IndexBuffer;
	extern Graphics::ConstantBuffer ConstantBuffers[(UINT)ConstantBufferType::End];

	extern ID3D11Buffer* ConstantBuffer;
	extern ID3D11InputLayout* InputLayouts;

	void Initialize();
	void Release();
}