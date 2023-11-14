#include "Event.h"

Event::Event(EventType type/* = EventType::None*/)
	: m_Type(type)
{
}

WindowCloseEvent::WindowCloseEvent()
	: Event(EventType::WindowClose)
{
}

KeyEvent::KeyEvent(EventType type, int keyCode)
	: Event(type), m_KeyCode(keyCode)
{
}

KeyPressedEvent::KeyPressedEvent(int keycode, int repeatCount)
	: KeyEvent(EventType::KeyPressed, keycode), m_RepeatCount(repeatCount)
{
}

KeyReleasedEvent::KeyReleasedEvent(int keycode)
	: KeyEvent(EventType::KeyReleased, keycode)
{
}

KeyTypedEvent::KeyTypedEvent(int keycode)
	: KeyEvent(EventType::KeyTyped, keycode)
{
}

MouseMovedEvent::MouseMovedEvent(float x, float y)
	: Event(EventType::MouseMoved), m_MouseX(x), m_MouseY(y)
{
}

MouseScrolledEvent::MouseScrolledEvent(float xOffset, float yOffset)
	: Event(EventType::MouseScrolled), m_XOffset(xOffset), m_YOffset(yOffset)
{
}

MouseButtonEvent::MouseButtonEvent(EventType type, int button)
	: Event(type), m_Button(button)
{
}

MouseButtonPressedEvent::MouseButtonPressedEvent(int button)
	: MouseButtonEvent(EventType::MouseButtonPressed, button)
{
}

MouseButtonReleasedEvent::MouseButtonReleasedEvent(int button)
	: MouseButtonEvent(EventType::MouseButtonReleased, button)
{
}
