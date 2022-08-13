#define FULL_WINTARD
#include "../Header/Headers.h"
#include "../Header/GDIPlusManager.h"
#include <algorithm>

//  The following two cannot change the order
namespace Gdiplus
{
	using std::min;
	using std::max;
}
#include <gdiplus.h>



ULONG_PTR GDIPlusManager::token = 0;
int GDIPlusManager::refCount = 0;

GDIPlusManager::GDIPlusManager()
{
	if (refCount++ == 0)
	{
		Gdiplus::GdiplusStartupInput input;
		input.GdiplusVersion = 1;
		input.DebugEventCallback = nullptr;
		input.SuppressBackgroundThread = false;
		Gdiplus::GdiplusStartup(&token, &input, nullptr);
	}
}

GDIPlusManager::~GDIPlusManager()
{
	if (--refCount == 0)
	{
		Gdiplus::GdiplusShutdown(token);
	}
}
