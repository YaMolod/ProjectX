#pragma once
#include <sstream>
#include <map>
#include <functional>

enum class EventType
{
	None = 0,
	WindowClose,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

namespace
{
	std::map<EventType, std::string> Events =
	{
		{EventType::None, "None"},
		{EventType::WindowClose, "WindowClose"},
		{EventType::KeyPressed, "KeyPressed"},
		{EventType::KeyPressed, "KeyPressed"},
		{EventType::KeyReleased, "KeyReleased"},
		{EventType::KeyTyped, "KeyTyped"},
		{EventType::MouseButtonPressed, "MouseButtonPressed"},
		{EventType::MouseButtonReleased, "MouseButtonReleased"},
		{EventType::MouseMoved, "MouseMoved"},
		{EventType::MouseScrolled, "MouseScrolled"}
	};

}

class Event
{
	friend class EventDispatcher;
public:
	Event(EventType type = EventType::None);
	virtual ~Event() = default;

	virtual std::string ToString() const { return GetName(); }

	EventType GetEventType() const { return m_Type; }
	const std::string GetName() const{ return Events[m_Type]; }

protected:
	bool m_Handled{ false };
	EventType m_Type{ EventType::None };
};

class EventDispatcher
{
public:
	using EventCallbackFn = std::function<bool(Event&)>;

	EventDispatcher(Event& event)
		: m_Event(event)
	{}

	bool Dispatch(EventType type, EventCallbackFn func)
	{
		if (m_Event.GetEventType() == type)
		{
			m_Event.m_Handled = func(m_Event);
			return true;
		}
		return false;
	}
private:
	Event& m_Event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
	return os << e.ToString();
}

class WindowCloseEvent : public Event
{

public:
	WindowCloseEvent();
};

class KeyEvent : public Event
{
public:
	virtual ~KeyEvent() = default;
	inline int GetKeyCode() const { return m_KeyCode; }

protected:
	KeyEvent(EventType type, int keyCode);

	int m_KeyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(int keycode, int repeatCount);

	inline int GetRepeatCount() const { return m_RepeatCount; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
		return ss.str();
	}

private:
	int m_RepeatCount;
};

class KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(int keycode);
		
	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_KeyCode;
		return ss.str();
	}
};

class KeyTypedEvent : public KeyEvent
{
public:
	KeyTypedEvent(int keycode);

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyTypedEvent: " << m_KeyCode;
		return ss.str();
	}
};

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(float x, float y);

	inline float GetX() const { return m_MouseX; }
	inline float GetY() const { return m_MouseY; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
		return ss.str();
	}

private:
	float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(float xOffset, float yOffset);
		
	inline float GetXOffset() const { return m_XOffset;}
	inline float GetYOffset() const { return m_YOffset; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
		return ss.str();
	}

private:
	float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public Event
{
public:
	virtual ~MouseButtonEvent() = default;
	inline int GetMouseButton() const { return m_Button; }

protected:
	MouseButtonEvent(EventType type, int button);

	int m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(int button);

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << m_Button;
		return ss.str();
	}
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(int button);

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << m_Button;
		return ss.str();
	}
};
