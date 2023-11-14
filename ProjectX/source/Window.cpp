#include "Window.h"


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
	glfwSetWindowUserPointer(m_Window, &m_Data);

	bgfx::renderFrame();
	bgfx::Init init;
	init.type = bgfx::RendererType::OpenGL;
	init.platformData.nwh = glfwGetWin32Window(m_Window);
	init.resolution.width  = m_Props.Width;
	init.resolution.height = m_Props.Height;

	m_Debug  = BGFX_DEBUG_TEXT;
	bgfx::init(init);
	bgfx::setDebug(m_Debug);

	const bgfx::ViewId kClearView = 0;
	bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
				, 0x303030ff
				, 1.0f
				, 0
				);

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
	{
		WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		WindowCloseEvent event;
		data.EventCallback(event);
	});
}

void Window::ShutDown()
{
	glfwDestroyWindow(m_Window);
	bgfx::shutdown();
}

void Window::OnUpdate()
{
	glfwPollEvents();
	bgfx::frame();
}
