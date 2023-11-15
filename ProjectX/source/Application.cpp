#include "Application.h"
#include <Mmsystem.h>
#include <mciapi.h>

#pragma comment(lib, "Winmm.lib")

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
	mciSendString(L"open \"assets/audio/free bird.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
	mciSendString(L"play mp3 repeat", NULL, 0, NULL);
	while (m_Running)
	{
		m_Scene->OnUpdate();
		m_Window->OnUpdate();
	}
}

void Application::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch(EventType::WindowClose, [&](Event& event) { return OnWindowClose(event); });
}

bool Application::OnWindowClose(Event& event)
{
	m_Running = false;
	return true;
}

int main(int argc, char **argv)
{
	Application app;
	app.Run();
}