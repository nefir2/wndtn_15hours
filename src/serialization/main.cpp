#include <iostream>
#include <vector>

namespace EventSystem {

	class Event;

	class System {
	private:
		friend class Event;
		std::string name;
		int32_t descriptor;
		int16_t index;
		bool active;
		std::vector<Event*> events;
	public:
		System(std::string);
		~System();
	public:
		void addEvent(Event*);
		Event* getEvent();
		bool isActive();
	};

	class Event {
	public:
		enum class DeviceType : int8_t {
			KEYBOARD = 1,
			MOUSE,
			TOUCHPAD,
			JOYSTICK
		};
		DeviceType dType;
		System* system = nullptr;
	public:
		Event(DeviceType);
		DeviceType getType();
		friend std::ostream& operator<<(std::ostream& stream, const DeviceType dType) {
			std::string result;
#define PRINT(a) result = #a; //stringify
			switch (dType)
			{
				case DeviceType::KEYBOARD: PRINT(KEYBOARD); break;
				case DeviceType::MOUSE: PRINT(MOUSE); break;
				case DeviceType::TOUCHPAD: PRINT(TOUCHPAD); break;
				case DeviceType::JOYSTICK: PRINT(JOYSTICK); break;
				default: break;
			}
			return stream << result;
		}
		void bind(System*, Event*);
	};

	class KeyboardEvent : public Event {
	private:
		int16_t keyCode;
		bool pressed;
		bool released;
	public:
		KeyboardEvent(int16_t, bool, bool);
		~KeyboardEvent();
	};


	//definition


	System::System(std::string name) : name(name), descriptor(123), index(1), active(true) {}
	System::~System() { /* TODO:: */ }
	void System::addEvent(Event* e) {
		e->bind(this, e);
	}
	Event* System::getEvent() {
		return events.front();
	}
	bool System::isActive() {
		return (bool)system; //there was: if (!system) return false; return true;
	}

	Event::Event(DeviceType dType) {
		this->dType = dType;
	}

	void Event::bind(System* system, Event* e) {
		this->system = system;
		this->system->events.push_back(e);
	}

	Event::DeviceType Event::getType() {
		return this->dType;
	}

	KeyboardEvent::KeyboardEvent(int16_t keyCode, bool pressed, bool released) : Event(Event::DeviceType::KEYBOARD), keyCode(keyCode), pressed(pressed), released(released) {}
}

using namespace EventSystem;

int main(int argc, char** argv) {
	System Foo("Foo");
	Event* e = new KeyboardEvent('a', true, false);

	Foo.addEvent(e);
	KeyboardEvent* kb = static_cast<KeyboardEvent*>(Foo.getEvent()); //better use this line, than less safe: (Keyboard*)Foo.getEvent();
	
	(void)argc;
	(void)argv;
	return 0;
}