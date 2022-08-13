#pragma once
#include "Window.h"
#include "MyTimer.h"
#include "ImguiManager.h"
#include "Pipeline/Camera.h"
class App
{
public: 
	App();
	~App();
	// master frame / message loop
	int Go();
private:
	void DoFrame();
private :
	ImguiManager imgui;
	float speedFactor = 1.f;
	Camera cam;
	Window wnd;
	MyTimer timer;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	static constexpr size_t nDrawables = 180;
};

