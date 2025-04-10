#include "event.h"
#include <random>

namespace EventSystem
{
	int32_t Event::getID() {
		return ID;
	}
	
	Event::Event(DeviceType dType) {
		std::random_device rd;
		std::uniform_int_distribution<> destr(1, 100);
		this->ID = destr(rd);
		this->dType = dType;
	}

	void Event::bind(System* system, Event* e) {
		this->system = system;
		this->system->events.push_back(e);
	}

	void Event::serialize(ObjectModel::Object* o) {
		ObjectModel::Primitive* ID = ObjectModel::Primitive::create("ID", ObjectModel::Type::I32, this->getID());
		ObjectModel::Primitive* dType = ObjectModel::Primitive::create("dType", ObjectModel::Type::I8, static_cast<int8_t>(this->dType));

		o->addEntity(ID);
		o->addEntity(dType);
	}

	Event::DeviceType Event::getType() {
		return this->dType;
	}
} // namespace EventSystem
