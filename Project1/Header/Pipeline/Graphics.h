#pragma once
#include "../Headers.h"
#include<d3d11.h>
#include <wrl.h>
#include <vector>
#include <memory>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "../MYException.h"
#include"DxgiInfoManager.h"
#include "../Macros/ConditionalNoexcept.h"

namespace Bind
{
	class Bindable;
}

class Graphics
{
	friend Bind::Bindable;
public:

	class Exception : public ChiliException
	{
		using ChiliException::ChiliException;
	};

	class HrException : public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {}) noexcept;
		const char* what()const noexcept override;
		const char* GetType()const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		HRESULT hr;
		std::string info;
	};

	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;
	public:
		const char* GetType() const noexcept override;
	private:
		std::string reason;
	};

	class InfoException : public Exception
	{
	public:
		InfoException(int line, const char* file, std::vector<std::string> infoMsgs = {}) noexcept;
		const char* what()const noexcept override;
		const char* GetType()const noexcept override;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string info;
	};

public: 
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	void SetCamera(DirectX::FXMMATRIX cam);
	DirectX::XMMATRIX GetCamera() const noexcept;
private:
	UINT width;
	UINT height;
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX camera;

public:

	Graphics(HWND hWnd, int Height, int Width);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();
	void BeginFrame(float red, float green, float blue) noexcept;
	void EndFrame(); 
	void DrawIndexed(UINT count) noxnd;

	void EnableImgui() noexcept;
	void DiableImgui() noexcept;
	bool IsImguiEnabled() const noexcept;
private:
	bool imguiEnabled = true;
private:
#ifndef NDEBUG
	DxgiInfoManager infoManager;
#endif
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
};

