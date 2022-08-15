#include "../../../Header/Pipeline/Bindable/Bindable.h"

namespace Bind
{
	ID3D11Device* Bindable::GetDevice(Graphics& gfx) noexcept
	{
		return gfx.pDevice.Get();
	}

	ID3D11DeviceContext* Bindable::GetContext(Graphics& gfx) noexcept
	{
		return gfx.pContext.Get();
	}

	DxgiInfoManager& Bindable::GetInfoManager(Graphics& gfx) noxnd
	{
		return gfx.infoManager;
	}

}

