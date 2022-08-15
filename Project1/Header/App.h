#pragma once
#include "Window.h"
#include "MyTimer.h"
#include "ImguiManager.h"
#include "Pipeline/Camera.h"
#include "Pipeline/Lights/PointLight.h"
#include <set>

class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame();

private:
	ImguiManager imgui;
	Window wnd;
	MyTimer timer;


	float speedFactor = 1.0f;
	Camera cam;
	PointLight light;

};