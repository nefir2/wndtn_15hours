#pragma once

#include "event.h"

namespace Core {
	class WindowResizedEvent : public Event {
	private:
		int width, height;
	public:
		WindowResizedEvent(int width, int height) : Event("Window resized event", Event::EventType::WINDOW_RESIZED_EVENT), width(width), height(height) {}
	public:
		std::string format() const override {
			std::string formatted = name + ": w" + std::to_string(width) + " h" + std::to_string(height);
			return formatted;
		}
	};

	class WindowClosedEvent : public Event {
	public:
		WindowClosedEvent() : Event("Window closed event", Event::EventType::WINDOW_RESIZED_EVENT) {}
	public:
		std::string format() const override {
			return name;
		}
	};
}