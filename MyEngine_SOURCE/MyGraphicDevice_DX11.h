#pragma once
#include "MyGraphics.h"

//https://github.com/kevinmoran/BeginnerDirect3D11

namespace Source::Graphics
{
	class GraphicDevice_DX11
	{
	public:
		GraphicDevice_DX11();
		~GraphicDevice_DX11();


		void Initialize();
		void Draw();

	private:
		bool CreateDevice();
		bool CreateSwapChain(DXGI_SWAP_CHAIN_DESC desc);
		bool GetBuffer(UINT buffer, REFIID riid, void** surface);
		bool CreateRenderTargetView(ID3D11Resource* resource, const D3D11_RENDER_TARGET_VIEW_DESC* desc, ID3D11RenderTargetView** renderTargetView);
		bool CreateDepthStencilView(ID3D11Resource* resource, const D3D11_DEPTH_STENCIL_VIEW_DESC* desc, ID3D11DepthStencilView** depthStencilView);
		bool CreateTexture2D(const D3D11_TEXTURE2D_DESC* desc,const D3D11_SUBRESOURCE_DATA* initialData, ID3D11Texture2D** texture2D);
		bool CreateVertexShader(const std::wstring& fileName, ID3DBlob** code, ID3D11VertexShader** vertexShader);
		bool CreatePixelShader(const std::wstring& fileName, ID3DBlob** code, ID3D11PixelShader** pixelShader);
		bool CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* inputElementDescs, UINT numElements,
			const void* shaderBytecodeWithInputSignature, SIZE_T bytecodeLength, ID3D11InputLayout** inputLayout);
		bool CreateBuffer(const D3D11_BUFFER_DESC* desc, const D3D11_SUBRESOURCE_DATA* initialData, ID3D11Buffer** buffer);
		
		void BindConstantBuffer(ShaderStage stage, CBType type, ID3D11Buffer* buffer);

		Microsoft::WRL::ComPtr<ID3D11Device> _device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _context;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _renderTarget;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _depthStencil;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthStencilView;

		Microsoft::WRL::ComPtr<IDXGISwapChain>	_swapChain;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> _samplers;
	};

	// This is a helper to get access to a global device instance
	//	- The engine uses this, but it is not necessary to use a single global device object
	//	- This is not a lifetime managing object, just a way to globally expose a reference to an object by pointer
	inline GraphicDevice_DX11*& GetDevice()
	{
		static GraphicDevice_DX11* device = nullptr;
		return device;
	}
}