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
	void ShowModelWindow();
private:
	ImguiManager imgui;
	Window wnd;
	MyTimer timer;


	float speedFactor = 1.0f;
	Camera cam;
	PointLight light;

	Model nano{ wnd.Gfx(),"Models\\nanosuit.obj" };

	struct
	{
		float roll = 0.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	} pos;
};