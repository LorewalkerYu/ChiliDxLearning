#include "../../../Header/Pipeline/Bindable/VertexBuffer.h"



void VertexBuffer::Bind(Graphics& gfx) noexcept
{
	// bind vertex buffer to pipeline
	
	const UINT offset = 0u;

	GetContext(gfx)->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
}
