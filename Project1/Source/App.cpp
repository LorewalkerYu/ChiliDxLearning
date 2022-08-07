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
}

void App::DoFrame()
{
	/*std::ostringstream oss;
	oss << (wnd.mouse.IsInWindow() ? "in" : "out") << "x: " << wnd.mouse.GetPosX() / 400.f - 1.f << "  y: " << wnd.mouse.GetPosY() / 300.f + 1.f;
	wnd.SetTitle(oss.str().c_str());*/
	const float c = sin(timer.Peek()) / 2.f + .5f;
	wnd.Gfx().ClearBuffer(c, c, 1.0f);
	wnd.Gfx().DrawTriangle(timer.Peek(),0, 0);

	wnd.Gfx().DrawTriangle(timer.Peek(), wnd.mouse.GetPosX() / 400.f - 1.f, -wnd.mouse.GetPosY() / 300.f + 1.f);
	wnd.Gfx().EndFrame();
}
