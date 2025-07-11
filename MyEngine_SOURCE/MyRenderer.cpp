#include "MyRenderer.h"
#include "MyGraphicDevice_DX11.h"
#include "MyResources.h"
#include "MyShader.h"


namespace Source::Renderer
{
	Camera* MainCamera = nullptr;

	std::vector<Graphics::Vertex> Vertexes = {};
	std::vector<UINT> Indices = {};

	Graphics::VertexBuffer VertexBuffer;
	Graphics::IndexBuffer IndexBuffer;
	Graphics::ConstantBuffer ConstantBuffers[(UINT)ConstantBufferType::End] = {};

	ID3D11Buffer* ConstantBuffer = nullptr;
	ID3D11InputLayout* InputLayouts = nullptr;
	
	// ====================== 임시 =========================
	void LoadTriangleMesh()
	{
		Renderer::Vertexes.resize(3);

		Renderer::Vertexes[0].Position = Vector3(0.f, 0.5f, 0.0f);
		Renderer::Vertexes[0].Color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		Renderer::Vertexes[1].Position = Vector3(0.5f, -0.5f, 0.0f);
		Renderer::Vertexes[1].Color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		Renderer::Vertexes[2].Position = Vector3(-0.5f, -0.5f, 0.0f);
		Renderer::Vertexes[2].Color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		Indices.push_back(0);
		Indices.push_back(1);
		Indices.push_back(2);
	}

	void LoadMeshes()
	{
		LoadTriangleMesh();
	}
	// =====================================================

	void LoadShaders()
	{
		Source::Resources::Load<Graphics::Shader>(L"TriangleShader", L"..\\Shaders_SOURCE\\Triangle");
	}

	void LoadConstantBuffers()
	{
		//GPU의 기본 크기 단위인16바이트를 맞추기 위해 Vector4를 사용
		ConstantBuffers[(UINT)ConstantBufferType::Transform].Create(ConstantBufferType::Transform, sizeof(Vector4));
	}

	void Initialize()
	{
		LoadMeshes();
		LoadShaders();
		LoadConstantBuffers();
	}

	void Release()
	{
		InputLayouts->Release();
	}
}