
#include "../../Header/Pipeline/Graphics.h"
#include "../../dxerr/dxerr.h"
#include "../../Header/Window.h"
#include "../../Header/Pipeline/GFXMacros.h"

#include <d3dcompiler.h>
#include <sstream>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;



//
//void Graphics::DrawTriangle(float angle, float x, float z)
//{
//	namespace wrl = Microsoft::WRL;
//	HRESULT hr;
//
//	// Vertex format
//	struct Vertex
//	{
//		struct
//		{
//			float x;
//			float y;
//			float z;
//		}pos;
//	};
//
//
//	const Vertex vertices[] =
//	{
//		{ -1.f, -1.f, -1.f},
//		{  1.f, -1.f, -1.f},
//		{ -1.f,  1.f, -1.f},
//		{  1.f,  1.f, -1.f},
//		{ -1.f, -1.f,  1.f},
//		{  1.f, -1.f,  1.f},
//		{ -1.f,  1.f,  1.f},
//		{  1.f,  1.f,  1.f},
//
//	};
//
//	// create vertex buffer
//	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
//	D3D11_BUFFER_DESC bd = {};
//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.CPUAccessFlags = 0u;
//	bd.MiscFlags = 0u;
//	bd.ByteWidth = sizeof(vertices);
//	bd.StructureByteStride = sizeof(Vertex);
//
//	D3D11_SUBRESOURCE_DATA sd = {};
//	sd.pSysMem = vertices;
//
//	GFX_THROW_INFO(pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer));
//
//	// bind vertex buffer to pipeline
//	const UINT stride = sizeof(Vertex);
//	const UINT offset = 0u;
//
//	pContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
//
//
//
//	// Create index buffer
//	const unsigned short indices[] =
//	{
//		0,2,1,2,3,1,
//		1,3,5,3,7,5,
//		2,6,3,3,6,7,
//		4,5,7,4,7,6,
//		0,4,2,2,4,6,
//		0,1,4,1,5,4
//	};
//	wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
//	D3D11_BUFFER_DESC ibd = {};
//	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
//	ibd.Usage = D3D11_USAGE_DEFAULT;
//	ibd.CPUAccessFlags = 0u;
//	ibd.MiscFlags = 0u;
//	ibd.ByteWidth = sizeof(indices);
//	ibd.StructureByteStride = sizeof(unsigned short);
//
//	D3D11_SUBRESOURCE_DATA isd = {};
//	isd.pSysMem = indices;
//
//	GFX_THROW_INFO(pDevice->CreateBuffer(&ibd, &isd, &pIndexBuffer));
//
//	// bind index buffer to pipeline
//	pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
//
//
//	// create contant buffer for tranformation matrix
//	struct ConstantBuffer
//	{
//		dx::XMMATRIX transform;
//	};
//	const ConstantBuffer cb =
//	{
//		{
//			dx::XMMatrixTranspose
//			(
//				dx::XMMatrixRotationZ(angle)*
//				dx::XMMatrixRotationX(angle) *
//				dx::XMMatrixTranslation(x,0, z + 4.f) *
//				dx::XMMatrixPerspectiveLH(1.f, .75f, .5f, 10.f)
//			)
//		}
//	};
//	 
//	wrl::ComPtr<ID3D11Buffer> pConstantBuffer;
//	D3D11_BUFFER_DESC cbd = {};
//	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	cbd.Usage = D3D11_USAGE_DYNAMIC;
//	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//	cbd.MiscFlags = 0u;
//	cbd.ByteWidth = sizeof(cb);
//	cbd.StructureByteStride = 0u;
//	D3D11_SUBRESOURCE_DATA csd = {};
//	csd.pSysMem = &cb;
//	GFX_THROW_INFO(pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer));
//	// bind constant buffer to vertex shader
//	pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
//
//
//	struct ConstantBuffer2
//	{
//		struct
//		{
//			float r;
//			float g;
//			float b;
//			float a;
//		}face_colors[6];
//	};
//	const ConstantBuffer2 cb2 =
//	{
//		{
//			{1.f, 0.f, 1.f},
//			{1.f, 0.f, 0.f},
//			{0.f, 1.f, 0.f},
//			{0.f, 0.f, 1.f},
//			{1.f, 1.f, 0.f},
//			{0.f, 1.f, 1.f},
//		}
//	};
//
//	wrl::ComPtr<ID3D11Buffer> pConstantBuffer2;
//	D3D11_BUFFER_DESC cbd2 = {};
//	cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	cbd2.Usage = D3D11_USAGE_DYNAMIC;
//	cbd2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//	cbd2.MiscFlags = 0u;
//	cbd2.ByteWidth = sizeof(cb2);
//	cbd2.StructureByteStride = 0u;
//	D3D11_SUBRESOURCE_DATA csd2 = {};
//	csd2.pSysMem = &cb2;
//	GFX_THROW_INFO(pDevice->CreateBuffer(&cbd2, &csd2, &pConstantBuffer2));
//	// bind constant buffer to pixel shader
//	pContext->PSSetConstantBuffers(0u, 1u, pConstantBuffer2.GetAddressOf());
//
//
//	// create pixel shader
//	wrl::ComPtr<ID3DBlob> pBlob;
//	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
//	GFX_THROW_INFO(D3DReadFileToBlob(L"PixelShader.cso", &pBlob));
//	GFX_THROW_INFO(pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));
//
//	// bind pixel shader
//	pContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);
//
//	// create Vertex shader
//	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
//	
//	GFX_THROW_INFO(D3DReadFileToBlob(L"VertexShader.cso", &pBlob));
//	GFX_THROW_INFO(pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader));
//
//	// bind vertex shader
//	pContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);
//
//
//
//	// input layout
//	wrl::ComPtr<ID3D11InputLayout> pInputLayout;
//	const D3D11_INPUT_ELEMENT_DESC ied[] =
//	{
//		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA,0 }
//	};
//	GFX_THROW_INFO(pDevice->CreateInputLayout(
//		ied, (UINT)std::size(ied),
//		pBlob->GetBufferPointer(),
//		pBlob->GetBufferSize(),
//		&pInputLayout
//	));
//	// bind input layout
//	pContext->IASetInputLayout(pInputLayout.Get());
//	
//	// bind render target
//	pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), nullptr);
//
//	// set primitive topology to triangle list
//	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//	// configure viewport
//	D3D11_VIEWPORT vp;
//	vp.Width = 800;
//	vp.Height = 600;
//	vp.MinDepth = 0;
//	vp.MaxDepth = 1;
//	vp.TopLeftX = 0;
//	vp.TopLeftY = 0;
//	pContext->RSSetViewports(1u, &vp);
//
//
//	GFX_THROW_INFO_ONLY( pContext->DrawIndexed((UINT)std::size(indices), 0u, 0u));
//}

void Graphics::SetProjection(DirectX::FXMMATRIX proj) noexcept
{
	projection = proj;
}

DirectX::XMMATRIX Graphics::GetProjection() const noexcept
{
	return projection;
}

void Graphics::SetCamera(DirectX::FXMMATRIX cam)
{
	camera = cam;
}

DirectX::XMMATRIX Graphics::GetCamera() const noexcept
{
	return camera;
}

Graphics::Graphics(HWND hWnd, int Height, int Width)
	:
	height(Height),
	width(Width)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;        // Pixel format  RGBA 8 
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;


	UINT swapCreateFlags = 0u;
#ifndef NDEBUG
	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr;

	// Create device and front/back buffer, swap chain and rendering context
	GFX_THROW_INFO(D3D11CreateDeviceAndSwapChain(
		nullptr,                         // Nullptr as default adapter
		D3D_DRIVER_TYPE_HARDWARE,      
		nullptr,                        // 
		swapCreateFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	));

	// gain access to texture subresource in swap chain (back buffer)
	wrl::ComPtr<ID3D11Resource> pBackBuffer;
	GFX_THROW_INFO(pSwap->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer));
	GFX_THROW_INFO(pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget));


	// Depth Stencil State
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	wrl::ComPtr<ID3D11DepthStencilState> pDSState;
	GFX_THROW_INFO(pDevice->CreateDepthStencilState(&dsDesc, pDSState.GetAddressOf()));

	pContext->OMSetDepthStencilState(pDSState.Get(), 1u);


	// create depth stensil texture
	wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Quality = 0U;
	descDepth.SampleDesc.Count = 1U;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.Usage = D3D11_USAGE_DEFAULT;

	GFX_THROW_INFO(pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil));

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0u;
	GFX_THROW_INFO(pDevice->CreateDepthStencilView(pDepthStencil.Get(), &descDSV, &pDSV));

	pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), pDSV.Get());


	// configure viewport
	D3D11_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	pContext->RSSetViewports(1u, &vp);


	// init imgui d3d impl
	ImGui_ImplDX11_Init(pDevice.Get(), pContext.Get());
}
Graphics::~Graphics()
{
	ImGui_ImplDX11_Shutdown();
}

void Graphics::BeginFrame(float red, float green, float blue) noexcept
{
	if (imguiEnabled)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	const float color[] = { red,green,blue, 1.0f };
	pContext->ClearRenderTargetView(pTarget.Get(), color);
	pContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.f, 0u);
}

void Graphics::EndFrame()
{

	if (imguiEnabled)
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	HRESULT hr;

#ifndef NDEBUG
	infoManager.Set();
#endif

	if (FAILED(hr = pSwap->Present(1u, 0u)))
	{
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
		{
			throw GFX_DEVICE_REMOVED_EXCEPT(pDevice->GetDeviceRemovedReason());
		}
		else
		{
			throw GFX_EXCEPT(hr);
		}
	}

}

void Graphics::DrawIndexed(UINT count) noexcept
{
	GFX_THROW_INFO_ONLY(pContext->DrawIndexed(count, 0u, 0u));
}

void Graphics::EnableImgui() noexcept
{
	imguiEnabled = true;
}

void Graphics::DiableImgui() noexcept
{
	imguiEnabled = false;
}

bool Graphics::IsImguiEnabled() const noexcept
{
	return imguiEnabled;
}

// Graphics exception stuff
Graphics::HrException::HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs) noexcept
	:
	Exception(line, file),
	hr(hr)
{
	// join all info messages with newlines into single string
	for (const auto& m : infoMsgs)
	{
		info += m;
		info.push_back('\n');
	}
	// remove final newline if exists
	if (!info.empty())
	{
		info.pop_back();
	}
}

Window::HrException::HrException(int line, const char* file, HRESULT hr) noexcept
	:
	Exception(line, file),
	hr(hr)
{
}

const char* Graphics::HrException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Error String] " << GetErrorString() << std::endl
		<< "[Description] " << GetErrorDescription() << std::endl;
	if (!info.empty())
	{
		oss << "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
	}
	oss << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Graphics::HrException::GetType() const noexcept
{
	return "Chili Graphics Exception";
}

HRESULT Graphics::HrException::GetErrorCode() const noexcept
{
	return hr;
}

std::string Graphics::HrException::GetErrorString() const noexcept
{
	return DXGetErrorString(hr);
}

std::string Graphics::HrException::GetErrorDescription() const noexcept
{
	char buf[512];
	DXGetErrorDescription(hr, buf, sizeof(buf));
	return buf;
}

std::string Graphics::HrException::GetErrorInfo() const noexcept
{
	return info;
}


const char* Graphics::DeviceRemovedException::GetType() const noexcept
{
	return "Chili Graphics Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
}

Graphics::InfoException::InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept
	:
	Exception(line, file)
{
	// join all info messages with newlines into single string
	for (const auto& m : infoMsgs)
	{
		info += m;
		info.push_back('\n');
	}
	// remove final newline if exists
	if (!info.empty())
	{
		info.pop_back();
	}
}

const char* Graphics::InfoException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
	oss << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Graphics::InfoException::GetType() const noexcept
{
	return "Chili Graphics Info Exception";
}

std::string Graphics::InfoException::GetErrorInfo() const noexcept
{
	return info;
}

