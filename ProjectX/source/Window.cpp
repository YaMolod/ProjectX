#include "Window.h"
#include "bgfxUtils/bgfxUtils.h"
#include "bgfxUtils/entry.h"


Window::Window(const WindowProps& props)
	: m_Props(props)
{
	Init();
}

Window::~Window()
{
}

void Window::Init()
{
	int success = glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	m_Window = glfwCreateWindow(static_cast<int>(m_Props.Width), static_cast<int>(m_Props.Height), m_Props.Title.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(m_Window, &m_Props);

	bgfx::renderFrame();
	bgfx::Init init;
	init.platformData.nwh = glfwGetWin32Window(m_Window);
	init.resolution.width  = m_Props.Width;
	init.resolution.height = m_Props.Height;
	bgfx::init(init);

	m_Debug  = BGFX_DEBUG_NONE;

	const bgfx::ViewId kClearView = 0;
	bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
	bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
}

void Window::ShutDown()
{
	glfwDestroyWindow(m_Window);
	bgfx::shutdown();
}

void Window::OnUpdate()
{
	glfwPollEvents();
	bgfx::touch(0);
	bgfx::dbgTextClear();
	bgfx::dbgTextPrintf(0, 0, 0x0f, "Press F1 to toggle stats.");
	bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");
	bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
	bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");
	const bgfx::Stats* stats = bgfx::getStats();
	bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.", stats->width, stats->height, stats->textWidth, stats->textHeight);
	bgfx::setDebug(BGFX_DEBUG_TEXT);
	bgfx::frame();
}
