#pragma once
#include "Bindable.h"
#include "../Vertex.h"
class VertexBuffer : public Bindable
{
public:
	template<class V>
	VertexBuffer(Graphics& gfx, const std::vector<V>& vertices)
		:
		stride(sizeof(V))
	{
		INFOMAN(gfx);

		// create vertex buffer

		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.ByteWidth = vertices.size() * sizeof(V);
		bd.StructureByteStride = sizeof(V);

		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices.data();

		GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&bd, &sd, &pVertexBuffer));



	}
	VertexBuffer(Graphics& gfx, const hw3dexp::VertexBuffer& vbuf)
		:
		stride((UINT)vbuf.GetLayout().Size())
	{
		INFOMAN(gfx);

		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.ByteWidth = UINT(vbuf.SizeBytes());
		bd.StructureByteStride = stride;
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vbuf.GetData();
		GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&bd, &sd, &pVertexBuffer));
	}
	virtual void Bind(Graphics& gfx) noexcept override;

protected:

	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	UINT stride;
};