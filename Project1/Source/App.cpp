#include "../Header/App.h"

#include "../Header/Pipeline/Drawable/AssTest.h"
#include "../Header/MyMath.h"

// for gdi initialize
#include "../Header/GDIPlusManager.h"
GDIPlusManager gdipm;

#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"
namespace dx = DirectX;

App::App()
	:
	wnd(800, 600, "The Donkey Fart Box"),
	light(wnd.Gfx())
{
	


	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

void App::DoFrame()
{
	const auto dt = timer.Mark() * speedFactor;
	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
	wnd.Gfx().SetCamera(cam.GetMatrix());
	light.Bind(wnd.Gfx(), cam.GetMatrix());

	const auto transform = dx::XMMatrixRotationRollPitchYaw(pos.roll, pos.pitch, pos.yaw) *
		dx::XMMatrixTranslation(pos.x, pos.y, pos.z);
	nano.Draw(wnd.Gfx(), transform);

	light.Draw(wnd.Gfx());

	// imgui windows

	cam.SpawnControlWindow();
	light.SpawnControlWindow();


	// present
	wnd.Gfx().EndFrame();
}

void App::ShowModelWindow()
{
	if (ImGui::Begin("Model"))
	{
		using namespace std::string_literals;

		ImGui::Text("Orientation");
		ImGui::SliderAngle("Roll", &pos.roll, -180.0f, 180.0f);
		ImGui::SliderAngle("Pitch", &pos.pitch, -180.0f, 180.0f);
		ImGui::SliderAngle("Yaw", &pos.yaw, -180.0f, 180.0f);

		ImGui::Text("Position");
		ImGui::SliderFloat("X", &pos.x, -20.0f, 20.0f);
		ImGui::SliderFloat("Y", &pos.y, -20.0f, 20.0f);
		ImGui::SliderFloat("Z", &pos.z, -20.0f, 20.0f);
	}
	ImGui::End();
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