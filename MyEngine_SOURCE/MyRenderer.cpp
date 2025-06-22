#include "MyRenderer.h"
#include "MyGraphicDevice_DX11.h"


namespace Source::Renderer
{
	Camera* MainCamera = nullptr;

	Vertex Vertexes[3] = {};
	std::vector<UINT> Indices = {};

	ID3D11Buffer* VertexBuffer = nullptr;
	ID3D11Buffer* IndexBuffer = nullptr;
	ID3D11Buffer* ConstantBuffer = nullptr;


	ID3DBlob* VertexBlob = nullptr;
	ID3D11VertexShader* VertexShader = nullptr;

	ID3DBlob* PixelBlob = nullptr;
	ID3D11PixelShader* PixelShader = nullptr;
	ID3D11InputLayout* InputLayouts = nullptr;
	
	// ====================== юс╫ц =========================
	void LoadTriangleMesh()
	{
		Renderer::Vertexes[0].position = Vector3(0.f, 0.5f, 0.0f);
		Renderer::Vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		Renderer::Vertexes[1].position = Vector3(0.5f, -0.5f, 0.0f);
		Renderer::Vertexes[1].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		Renderer::Vertexes[2].position = Vector3(-0.5f, -0.5f, 0.0f);
		Renderer::Vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		Indices.push_back(0);
		Indices.push_back(1);
		Indices.push_back(2);
	}

	void LoadMeshes()
	{
		LoadTriangleMesh();
	}
	// =====================================================

	void Initialize()
	{
		LoadMeshes();
	}

	void Release()
	{
		VertexBuffer->Release();
		VertexBlob->Release();
		VertexShader->Release();
		PixelBlob->Release();
		PixelShader->Release();
		InputLayouts->Release();
		IndexBuffer->Release();
		ConstantBuffer->Release();
	}
}