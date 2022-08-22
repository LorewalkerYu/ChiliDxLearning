#pragma once
#include "Window.h"
#include "MyTimer.h"
#include "ImguiManager.h"
#include "Pipeline/Camera.h"
#include "Pipeline/Lights/PointLight.h"
#include <set>
#include "Pipeline/Drawable/Mesh.h"
class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame();
	void ShowImguiDemoWindow();
	void ShowRawInputWindow();
private:

	int x = 0, y = 0;
	ImguiManager imgui;
	Window wnd;
	MyTimer timer;
	float speedFactor = 1.0f;
	Camera cam;
	PointLight light;
	Model nano{ wnd.Gfx(),"Models\\nano_hierarchy.gltf" };

};