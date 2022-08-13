#pragma once
#include "Graphics.h"
class Camera
{
public:
	DirectX::XMMATRIX GetMatrix() const noexcept;
	void SpawnControlWindow() noexcept;
	void Reset() noexcept;
private:
	float r     = 20.f;           // distance away from origin
	float theta = 0.f;            // rotate around origin
	float phi   = 0.f;            // rotate around origin
	float pitch = 0.f;            // oritation
	float yaw   = 0.f;            // oritation
	float roll  = 0.f;            // oritation
};

