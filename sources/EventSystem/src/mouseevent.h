#include "event.h"

namespace Core {
	class MouseMovedEvent : public Event {
	private:
		int x, y;
	public:
		MouseMovedEvent(int x, int y) : Event("Mouse moved event", Event::EventType::MOUSE_MOVED_EVENT), x(x), y(y) {}
	public:
		std::string format() const override {
			std::string formatted = name + ": x" + std::to_string(x) + " y" + std::to_string(y);
			return formatted;
		}
	};

	class MouseScrolledEvent : public Event {
	private:
		int x; //horizontal mouse scroll
		int y; //vertical mouse scroll
	public:
		MouseScrolledEvent(int x, int y) : Event("Mouse scrolled Event", Event::EventType::MOUSE_SCROLLED_EVENT), x(x), y(y) {}
	public:
		std::string format() const override {
			std::string formatted = name + ": x" + std::to_string(x) + " y" + std::to_string(y);
			return formatted; // (y > 0) ? formatted = name + ": " + "to bottom" : formatted = name + ": " + "to top";
		}
	};

	class MouseButtonPressed : public Event {
	private:
		int button;
		int modifiers;
	public:
		MouseButtonPressed(int button, int modifiers) : Event("Mouse button pressed", Event::EventType::MOUSE_BUTTON_PRESSED_EVENT), button(button), modifiers(modifiers) {}
	public:
		std::string format() const override {
			std::string formatted = name + ": " + std::to_string(button) + ", modifiers' combination #" + std::to_string(modifiers);
			return formatted;
		}
	};

	class MouseButtonReleased : public Event {
	private:
		int button;
		int modifiers;
	public:
	MouseButtonReleased(int button, int modifiers) : Event("Mouse button released", Event::EventType::MOUSE_BUTTON_RELEASED_EVENT), button(button), modifiers(modifiers) {}
	public:
		std::string format() const override {
			std::string formatted = name + ": " + std::to_string(button);
			return formatted;
		}
	};
}