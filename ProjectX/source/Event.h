#pragma once
#include <sstream>

enum class EventType
{
	None = 0,
	WindowClose,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
							virtual EventType GetEventType() const override { return GetStaticType(); }\
							virtual const char* GetName() const override { return #type; }

class Event
{
	friend class EventDispatcher;
public:
	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual std::string ToString() const { return GetName(); }

	bool Handled = false;
};

class EventDispatcher
{
public:
	EventDispatcher(Event& event)
		: m_Event(event)
	{}

	template <typename T, typename F>
	bool Dispatch(const F& func)
	{
		if (m_Event.GetEventType() == T::GetStaticType())
		{
			m_Event.Handled = func(static_cast<T&>(m_Event));
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
	WindowCloseEvent() {}

	EVENT_CLASS_TYPE(WindowClose)
};

class KeyEvent : public Event
{
public:
	inline int GetKeyCode() const { return m_KeyCode; }

protected:
	KeyEvent(int keycode)
		: m_KeyCode(keycode)
	{
	}

	int m_KeyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(int keycode, int repeatCount)
		: KeyEvent(keycode), m_RepeatCount(repeatCount)
	{
	}

	inline int GetRepeatCount() const { return m_RepeatCount; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyPressed)

private:
	int m_RepeatCount;
};

class KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(int keycode)
		: KeyEvent(keycode)
	{
	}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent
{
public:
	KeyTypedEvent(int keycode)
		: KeyEvent(keycode)
	{
	}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyTypedEvent: " << m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyTyped)	
};

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(float x, float y)
		: m_MouseX(x), m_MouseY(y)
	{}

	inline float GetX() const { return m_MouseX; }
	inline float GetY() const { return m_MouseY; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseMoved)

private:
	float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(float xOffset, float yOffset)
		: m_XOffset(xOffset), m_YOffset(yOffset)
	{}

	inline float GetXOffset() const { return m_XOffset;}
	inline float GetYOffset() const { return m_YOffset; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseScrolled)

private:
	float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public Event
{
public:
	inline int GetMouseButton() const { return m_Button; }

protected:
	MouseButtonEvent(int button)
		: m_Button(button)
	{}

	int m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(int button)
		: MouseButtonEvent(button)
	{}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << m_Button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(int button)
		: MouseButtonEvent(button)
	{}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << m_Button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonReleased)
};
