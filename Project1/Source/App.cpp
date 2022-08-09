#include "../Header/App.h"
#include "../Header/Pipeline/Drawable/Box.h"

App::App()
	: wnd(800,600,"A Window")
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rdist(6.f, 20.f);
	for (int i = 0; i < 80; ++i)
	{
		boxes.push_back(std::make_unique<Box>(wnd.Gfx(), rng, adist, ddist, odist, rdist));
	}
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 0.75f, .5f, 40.f));
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
	auto dt = timer.Mark();
	wnd.Gfx().ClearBuffer(.07f, 0.f, .12f);
	for (auto& elem : boxes)
	{
		elem->Update(dt);
		elem->Draw(wnd.Gfx());
	}
	wnd.Gfx().EndFrame();
}
