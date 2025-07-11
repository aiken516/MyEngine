#pragma once
#include "MyResource.h"
#include "MyGraphicDevice_DX11.h"

namespace Source::Graphics
{
	class Shader : public Resource
	{
	public:
		Shader();
		virtual ~Shader();

		virtual HRESULT Load(const std::wstring path) override;
		
		bool Create(const ShaderStage shaderStage, const std::wstring& fileName);
		bool CreateVertexShader(const std::wstring& fileName);
		bool CreatePixelShader(const std::wstring& fileName);
		void Bind();

		Microsoft::WRL::ComPtr<ID3DBlob> GetVertexBlob() { return _vertexBlob; }
	private:

		Microsoft::WRL::ComPtr<ID3DBlob> _vertexBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> _hullBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> _domainBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> _geometryBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> _pixelBlob;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertexShader;
		Microsoft::WRL::ComPtr<ID3D11HullShader> _hullShader;
		Microsoft::WRL::ComPtr<ID3D11DomainShader> _domainShader;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> _geometryShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShader;
	};
}