#pragma once
#include "event.h"

namespace Core {
	class KeyPressedEvent : public Event {
	private:
		int key;
		int modifiers;
	public:
		KeyPressedEvent(int key, int modifiers) : Event("Key pressed event", Event::EventType::KEY_PRESSED_EVENT), key(key), modifiers(modifiers) {}
	public: 
		std::string format() const override {
			std::string formatted = name + ": " + (char)key + ", modifiers" + std::to_string(modifiers);
			return formatted;
		}
	};

	class KeyReleasedEvent : public Event {
	private:
		int key;
		int modifiers;
	public:
		KeyReleasedEvent(int key, int modifiers) : Event("Key released event", Event::EventType::KEY_RELEASED_EVENT), key(key), modifiers(modifiers) {}
	public: 
		std::string format() const override {
			std::string formatted = name + ": " + (char)key + ", modifiers" + std::to_string(modifiers);
			return formatted;
		}
	};

	class KeyRepeatedEvent : public Event {
	private:
		int key;
		int modifiers;
	public:
		KeyRepeatedEvent(int key, int modifiers) : Event("Key repeated event", Event::EventType::KEY_REPEATED_EVENT), key(key), modifiers(modifiers) {}
	public: 
		std::string format() const override {
			std::string formatted = name + ": " + (char)key + ", modifiers" + std::to_string(modifiers);
			return formatted;
		}
	};
}