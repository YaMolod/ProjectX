#include "Application.h"

Application::Application()
{
	m_Window = std::make_unique<Window>();
}

void Application::Run()
{
	while (m_Running)
	{
		m_Window->OnUpdate();
	}
}

int main(int argc, char **argv)
{
	Application app;
	app.Run();
}