#pragma once
#include <string>
#include <vector>
#include <serialization.h>
#include "event.h" //вместо того чтобы посреди класса объявлять о существовании Event - лучше просто указать его в хедерах.

namespace EventSystem
{
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
		void serialize();
	};
} // namespace EventSystem
