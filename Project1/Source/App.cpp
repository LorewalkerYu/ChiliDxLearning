#include "../Header/App.h"


#include "../Header/MyMath.h"

// for gdi initialize
#include "../Header/GDIPlusManager.h"
GDIPlusManager gdipm;

#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"
namespace dx = DirectX;

App::App()
	:
	wnd(1280, 720, "The Donkey Fart Box"),
	light(wnd.Gfx())
{
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 9.f / 16.f, 0.5f, 40.0f));

}

void App::DoFrame()
{
	const auto dt = timer.Mark() * speedFactor;
	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
	wnd.Gfx().SetCamera(cam.GetMatrix());
	light.Bind(wnd.Gfx(), cam.GetMatrix());


	nano.Draw(wnd.Gfx());

	light.Draw(wnd.Gfx());

	while (const auto e = wnd.kbd.ReadKey())
	{
		if (wnd.CursorEnabled())
		{
			wnd.DisableCursor();
			wnd.mouse.EnableRaw();
		}
		else
		{
			wnd.EnableCursor();
			wnd.mouse.DisableRaw();
		}
	}

	// imgui windows
	cam.SpawnControlWindow();
	light.SpawnControlWindow();
	ShowImguiDemoWindow();
	nano.ShowWindow();
	ShowRawInputWindow();
	// present
	wnd.Gfx().EndFrame();
}

void App::ShowRawInputWindow()
{
	while (const auto d = wnd.mouse.ReadRawDelta())
	{
		x += d->x;
		y += d->y;
	}
	if (ImGui::Begin("Raw Input"))
	{
		ImGui::Text("Tally: (%d,%d)", x, y);
		ImGui::Text("Cursor: %s", wnd.CursorEnabled() ? "enabled" : "disabled");

	}
	ImGui::End();
}

void App::ShowImguiDemoWindow()
{
	static bool show_demo_window = true;
	if (show_demo_window)
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}
}

App::~App()
{}


int App::Go()
{
	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessage())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}
}