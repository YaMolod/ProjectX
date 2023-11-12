#pragma once
#include "Window.h"
#include <memory>


class Application
{
public:
	Application();
	~Application() = default;

	void Run();

private:
	std::unique_ptr<Window> m_Window;
	bool m_Running{ true };
};

