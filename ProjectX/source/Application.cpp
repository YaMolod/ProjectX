#include "Application.h"

Application::Application()
{
	m_Window = std::make_unique<Window>();
	m_Scene = std::make_unique<Scene>();
	Init();
}

void Application::Init()
{
	m_Window->SetEventCallback([&](Event& event) { OnEvent(event); });
}

void Application::Run()
{
	while (m_Running)
	{
		m_Scene->OnUpdate();
		m_Window->OnUpdate();
	}
}

void Application::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowCloseEvent>([&](WindowCloseEvent& event) { return OnWindowClose(event); });
}

bool Application::OnWindowClose(WindowCloseEvent& event)
{
	m_Running = false;
	return true;
}

int main(int argc, char **argv)
{
	Application app;
	app.Run();
}