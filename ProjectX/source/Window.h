#pragma once
#include "Event.h"

#include <string>
#include <stdio.h>
#include <functional>
#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

struct WindowProps
{
	std::string Title;
	uint32_t Width;
	uint32_t Height;

	WindowProps(const std::string& title = "ProjectX",
		uint32_t width = 1280,
		uint32_t height = 720)
		: Title(title), Width(width), Height(height)
	{}
};

class Window
{
public:
	using EventCallbackFn = std::function<void(Event&)>;

	Window(const WindowProps& props = WindowProps());
	~Window();

	void Init();
	void ShutDown();
	void OnUpdate();

	void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

private:
	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;

		EventCallbackFn EventCallback;
	} m_Data;

	bgfx::UniformHandle u_time;
	GLFWwindow* m_Window{ nullptr };

	WindowProps m_Props;
	uint32_t m_Debug;

	
};

