#pragma once
#include <iostream>
#include "system.h"

namespace EventSystem
{
	class Event {
	private:
		int32_t ID;
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
		int32_t getID();
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
		void serialize(ObjectModel::Object*);
	};
} // namespace EventSystem
