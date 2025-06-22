#pragma once
#include "MyCamera.h"
#include "MyGraphicDevice_DX11.h"

namespace Source::Renderer
{
	extern Camera* MainCamera;

	struct Vertex
	{
		Vector3 position;
		Vector4 color;
	};

	extern Vertex Vertexes[3];
	extern std::vector<UINT> Indices;

	extern ID3D11Buffer* VertexBuffer;
	extern ID3D11Buffer* IndexBuffer;
	extern ID3D11Buffer* ConstantBuffer;

	extern ID3DBlob* VertexBlob;
	extern ID3D11VertexShader* VertexShader;

	extern ID3DBlob* PixelBlob;
	extern ID3D11PixelShader* PixelShader;
	extern ID3D11InputLayout* InputLayouts;

	void Initialize();
	void Release();
}