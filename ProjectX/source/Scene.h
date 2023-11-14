#pragma once
#include <bgfxUtils/bgfxUtils.h>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

class Scene
{
public:
	Scene();
	~Scene();

	void Init();
	void ShutDown();
	void OnUpdate();

private:
	Mesh* m_mesh{ nullptr };
	bgfx::ProgramHandle m_program;
	bgfx::UniformHandle u_time;
	int64_t m_timeOffset;
};

