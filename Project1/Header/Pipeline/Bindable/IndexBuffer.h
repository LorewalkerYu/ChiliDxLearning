#pragma once
#include "Bindable.h"
class IndexBuffer : public Bindable
{
public:
	IndexBuffer(Graphics& gfx, const std::vector<unsigned short>& indices);

	virtual void Bind(Graphics& gfx) noexcept override;

	UINT GetCount() const noexcept;
protected:

	UINT Count;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;

};

