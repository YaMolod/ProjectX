#pragma once
#include "Window.h"
#include "Scene.h"
#include <memory>


class Application
{
public:
	Application();
	~Application() = default;

	void Init();
	void Run();

	void OnEvent(Event& event);
	bool OnWindowClose(WindowCloseEvent& event);

private:
	std::unique_ptr<Window> m_Window;
	std::unique_ptr<Scene> m_Scene;
	bool m_Running{ true };
};

