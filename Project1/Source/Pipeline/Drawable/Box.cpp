#include "../../../Header/Pipeline/Drawable/Box.h"
#include "../../../Header/Pipeline/Bindable/BindableBase.h"
#include "../../../Header/Pipeline/GFXMacros.h"
#include "../../../Header/Geometry/Cube.h"

#include "../../../Header/Pipeline/Surface.h"
#include "../../../Header/Pipeline/Bindable/Texture.h"
#include "../../../Header/Pipeline/Bindable/Sampler.h"
Box::Box(Graphics& gfx, 
	std::mt19937& rng, 
	std::uniform_real_distribution<float>& adist, 
	std::uniform_real_distribution<float>& ddist, 
	std::uniform_real_distribution<float>& odist, 
	std::uniform_real_distribution<float>& rdist,
	std::uniform_real_distribution<float>& bdist)
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
	namespace dx = DirectX;
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			dx::XMFLOAT3 pos;
			struct
			{
				float u;
				float v;
			} tex;
		};

		const auto model = Cube::MakeSkinned<Vertex>();



		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));
		AddStaticBind(std::make_unique<Texture>(gfx, Surface::FromFile("Images\\cube.png")));
		AddStaticBind(std::make_unique<Sampler>(gfx));
		auto pVertexShader = std::make_unique<VertexShader>(gfx, L"HlslCSO\\TextureVS.cso");
		auto pVertexShaderBlob = pVertexShader->GetBytecode();
		AddStaticBind(std::move(pVertexShader));
		AddStaticBind(std::make_unique<PixelShader>(gfx, L"HlslCSO\\TexturePS.cso"));


		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));

		struct PixelShaderConstants
		{
			struct
			{
				float r;
				float g;
				float b;
				float a;
			}face_colors[8];
		};
		const PixelShaderConstants cb2 =
		{
			{
				{ 1.0f,1.0f,1.0f },
				{ 1.0f,0.0f,0.0f },
				{ 0.0f,1.0f,0.0f },
				{ 1.0f,1.0f,0.0f },
				{ 0.0f,0.0f,1.0f },
				{ 1.0f,0.0f,1.0f },
				{ 0.0f,1.0f,1.0f },
				{ 0.0f,0.0f,0.0f },
			}
		};

		AddStaticBind(std::make_unique<PixelConstantBuffer<PixelShaderConstants>>(gfx, cb2));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },

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

	// model deformation transform (per instance, not stored as bind)
	dx::XMStoreFloat3x3(
		&mt,
		dx::XMMatrixScaling(1.0f, 1.0f, bdist(rng))
	);


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
	return DirectX::XMLoadFloat3x3(&mt) *
		DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw,roll) *                 // Rotate around box center( = origin)
		DirectX::XMMatrixTranslation(r, 0.f, 0.f) *             // Translate box away from origin
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi,chi) *        //Rotate around origin
		DirectX::XMMatrixTranslation(0.f, 0.f,20.f);            // Translate box away form camera
}
