#include "../../../Header/Pipeline/Drawable/Box.h"
#include "../../../Header/Pipeline/Bindable/BindableBase.h"
#include "../../../Header/Pipeline/GFXMacros.h"
#include <iostream>
Box::Box(Graphics& gfx, 
	std::mt19937& rng, 
	std::uniform_real_distribution<float>& adist, 
	std::uniform_real_distribution<float>& ddist, 
	std::uniform_real_distribution<float>& odist, 
	std::uniform_real_distribution<float>& rdist)
	:
	r(rdist(rng)),
	droll(ddist(rng)),
	dpitch(ddist(rng)),
	dyaw(ddist(rng)),
	dphi(odist(rng)),
	dtheta(odist(rng)),
	dchi(odist(rng)),
	chi(adist(rng)),
	theta(adist(rng)),
	phi(adist(rng))
{
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			struct
			{
				float x;
				float y;
				float z;
			} pos;
		};

		const std::vector<Vertex> vertices =
		{
			{ -1.f, -1.f, -1.f},
			{  1.f, -1.f, -1.f},
			{ -1.f,  1.f, -1.f},
			{  1.f,  1.f, -1.f},
			{ -1.f, -1.f,  1.f},
			{  1.f, -1.f,  1.f},
			{ -1.f,  1.f,  1.f},
			{  1.f,  1.f,  1.f},

		};


		AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));

		auto pVertexShader = std::make_unique<VertexShader>(gfx, L"VertexShader.cso");
		auto pVertexShaderBlob = pVertexShader->GetBytecode();
		AddStaticBind(std::move(pVertexShader));
		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PixelShader.cso"));


		const std::vector<unsigned short> indices =
		{

			0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4

		};

		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));

		struct ConstantBuffer2
		{
			struct
			{
				float r;
				float g;
				float b;
				float a;
			}face_colors[6];
		};
		const ConstantBuffer2 cb2 =
		{
			{
				{1.f, 0.f, 1.f},
				{1.f, 0.f, 0.f},
				{0.f, 1.f, 0.f},
				{0.f, 0.f, 1.f},
				{1.f, 1.f, 0.f},
				{0.f, 1.f, 1.f},
			}
		};

		AddStaticBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2>>(gfx, cb2));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA,0 }
		};
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pVertexShaderBlob));
		AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	
	else
	{
		SetIndexBufferFromStatic();
	}
	// cus every box has its own transform
	AddBind(std::make_unique<TransformCbuf>(gfx, *this));


}

void Box::Update(float dt) noexcept
{
	roll += droll * dt;
	pitch += dpitch * dt;
	yaw += dyaw * dt;
	theta += dtheta * dt;
	chi += dchi * dt;
	phi += dphi * dt;

}

DirectX::XMMATRIX Box::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw,roll) *                 // Rotate around box center( = origin)
		DirectX::XMMatrixTranslation(r, 0.f, 0.f) *             // Translate box away from origin
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi,chi) *        //Rotate around origin
		DirectX::XMMatrixTranslation(0.f, 0.f,20.f);            // Translate box away form camera
}
