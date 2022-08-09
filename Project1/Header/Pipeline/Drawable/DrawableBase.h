#pragma once
#include "Drawable.h"
#include "../Bindable/Bindable.h"
template<class T>
class DrawableBase : public Drawable
{
//public:
//	bool IsStaticInitialized() const noexcept
//	{
//		return !staticBinds.empty();
//	}
//
//	void AddStaticBind(std::unique_ptr<Bindable> bind) noexcept
//	{
//		assert("*Must use* AddIndexBuffer to bind index buffer" && typeid(*bind));
//		staticBinds.push_back(std::move(bind));
//	}
//
//	void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> ibuf) noexcept
//	{
//		assert(pIndexBuffer = nullptr);
//		pIndexBuffer = iBuf.Get();
//		staticBinds.push_back(std::move(ibuf));
//	}
//private:
//	static std::vector<std::unique_ptr<Bindable>> staticBinds;
};

