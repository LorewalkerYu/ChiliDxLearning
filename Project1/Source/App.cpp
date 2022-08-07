#include "../Header/App.h"

App::App()
	: wnd(800,600,"A Window")
{
}

int App::Go()
{
	while (1)
	{
		if (const auto ecode = Window::ProcessMessage())
		{
			return *ecode;
		}
		DoFrame();
	}
	//// Message Bump
	//MSG msg;
	//BOOL gResult;
	//while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	//{
	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);
	//	DoFrame();
	//}
	//if (gResult == -1)
	//{
	//	return -1;
	//}
	//else
	//{
	//	return msg.wParam;
	//}
	//return 0;
}

void App::DoFrame()
{
	//const float t = timer.Peek();
	//std::ostringstream oss;
	//oss << "Timer elapsed: " << std::setprecision(1) << std::fixed << t << "s";
	//wnd.SetTitle(oss.str().c_str());
	const float c = sin(timer.Peek()) / 2.f + .5f;
	wnd.Gfx().ClearBuffer(c, c, 1.0f);
	wnd.Gfx().DrawTriangle();
	wnd.Gfx().EndFrame();
}
