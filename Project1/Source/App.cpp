#include "../Header/App.h"
#include "../Header/Pipeline/Drawable/Box.h"
#include "../Header/Pipeline/Drawable/Pyramid.h"
#include "../Header/Pipeline/Drawable/Melon.h"
#include "../Header/Pipeline/Drawable/Sheet.h"
#include "../Header/MyMath.h"

// for gdi initialize
#include "../Header/GDIPlusManager.h"
GDIPlusManager gdipm;

#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"
App::App()
	: wnd(800, 600, "A Window")
{
	class Factory
	{
	public:
		Factory(Graphics& gfx)
			:
			gfx(gfx)
		{}
		std::unique_ptr<Drawable> operator()()
		{
			switch (typedist(rng))
			{
			case 0:
				return std::make_unique<Pyramid>(
					gfx, rng, adist, ddist,
					odist, rdist
					);
			case 1:
				return std::make_unique<Box>(
					gfx, rng, adist, ddist,
					odist, rdist, bdist
					);
			case 3:
				return std::make_unique<Melon>(
					gfx, rng, adist, ddist,
					odist, rdist, longdist, latdist
					);
			case 2:
				return std::make_unique<Sheet>(
					gfx, rng, adist, ddist,
					odist, rdist
					);
			default:
				assert(false && "bad drawable type in factory");
				return {};
			}
		}
	private:
		Graphics& gfx;
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_real_distribution<float> adist{ 0.0f,PI * 2.0f };
		std::uniform_real_distribution<float> ddist{ 0.0f,PI * 0.5f };
		std::uniform_real_distribution<float> odist{ 0.0f,PI * 0.08f };
		std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
		std::uniform_real_distribution<float> bdist{ 0.4f,3.0f };
		std::uniform_int_distribution<int> latdist{ 5,20 };
		std::uniform_int_distribution<int> longdist{ 10,40 };
		std::uniform_int_distribution<int> typedist{ 0,2 };
	};

	Factory f(wnd.Gfx());
	drawables.reserve(nDrawables);

	std::generate_n
	(
		std::back_inserter(drawables),
		nDrawables, 
		f
	);

	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));

}
App::~App()
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
	auto dt = timer.Mark() * speedFactor;
	wnd.Gfx().SetCamera(cam.GetMatrix());


	wnd.Gfx().BeginFrame(.07f, 0.f, .12f);

	for (auto& d : drawables)
	{
		
		d->Update(wnd.kbd.KeyIsPressed(VK_SPACE)?0.f:dt);
		d->Draw(wnd.Gfx());
	}

	static char Buffer[1024];
	if (ImGui::Begin("Simulation Speed"))
	{
		ImGui::SliderFloat("Speed Factor", &speedFactor, 0.f, 4.f, "%.1f");
		ImGui::Text("Application acerage %.3f ms/frame (%.1f FPS)", 1000.f / ImGui::GetIO().Framerate, 1000.f / ImGui::GetIO().Framerate);
		ImGui::InputText("Butts", Buffer, sizeof(Buffer));
	}
	ImGui::End();
	// imgui window camera control
	cam.SpawnControlWindow();
	// present
	wnd.Gfx().EndFrame();

}
