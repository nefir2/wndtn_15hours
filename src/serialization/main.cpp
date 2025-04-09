#include <iostream>
#include <vector>
#include <bitset>
#include <assert.h>
#include <fstream>
#include <random>
#include <string>

namespace Core
{
	template<typename T>
	void encode(std::vector<int8_t>* buffer, int16_t* iterator, T value);
	template<>
	void encode<std::string>(std::vector<int8_t>* buffer, int16_t* iterator, std::string value);
	template<typename T>
	void encode(std::vector<int8_t>* buffer, int16_t* iterator, std::vector<T> value);
}

namespace ObjectModel {
	enum class Wrapper : int8_t {
		PRIMITIVE = 1,
		ARRAY,
		STRING,
		OBJECT
	};

	enum class Type : int8_t {
		I8 = 1,
		I16, 
		I32,
		I64,

		U8,
		U16,
		U32,
		U64,

		FLOAT,
		DOUBLE,

		BOOL
	};

	class Root {
	protected:
		std::string name;
		int16_t nameLength;
		int8_t wrapper;
		int32_t size;
	protected:
		Root();
	public: 
		int32_t getSize();
		void setName(std::string);
		std::string getName();
		virtual void pack(std::vector<int8_t>*, int16_t*);
	};

	class Primitive : public Root {
	private:
		int8_t type = 0;
		std::vector<int8_t>* data = nullptr;
	private:
		Primitive();
	public:
		template<typename T>
		static Primitive* create(std::string name, Type type, T value) {
			Primitive* p = new Primitive();
			p->setName(name);
			p->wrapper = static_cast<int8_t>(Wrapper::PRIMITIVE);
			p->type = static_cast<int8_t>(type);
			p->data = new std::vector<int8_t>(sizeof(T)); //здесь он оставил как было sizeof value. 
			p->size += p->data->size();
			int16_t iterator = 0;
			Core::template encode<T>(p->data, &iterator, value);
			return p;
		}
		void pack(std::vector<int8_t>*, int16_t*);
	};

	class Array : public Root {
	private:
		int8_t type = 0;
		int32_t count = 0;
		std::vector<int8_t>* data = nullptr;
	private:
		Array();
	public:
		template<typename T>
		static Array* createArray(std::string name, Type type, std::vector<T> value) {
			Array* arr = new Array();
			arr->setName(name);
			arr->wrapper = static_cast<int8_t>(Wrapper::ARRAY);
			arr->type = static_cast<int8_t>(type);
			arr->count = value.size();
			arr->data = new std::vector<int8_t>(sizeof(T) * value.size());
			arr->size += value.size() * sizeof(T);
			int16_t iterator = 0;
			Core::template encode<T>(arr->data, &iterator, value);
			return arr;
		}
		template<typename T>
		static Array* createString(std::string name, Type type, T value) {
			Array* str = new Array();
			str->setName(name);
			str->wrapper = static_cast<int8_t>(Wrapper::STRING);
			str->type = static_cast<int8_t>(type);
			str->count = value.size();
			str->data = new std::vector<int8_t>(value.size());
			str->size += value.size();
			int16_t iterator = 0;
			Core::template encode<T>(str->data, &iterator, value);
			return str;
		}

		void pack(std::vector<int8_t>*, int16_t*);
	};

	class Object : public Root {
	private:
		std::vector<Root*> entities;
		int16_t count = 0;
	public:
		Object(std::string);
		void addEntity(Root* r);
		Root* findByName(std::string);
		void pack(std::vector<int8_t>*, int16_t*);
	};
} 


namespace Core {
	namespace Util {
		bool isLittleEndian() {
			// 0x00 0x00 0x00 0b0000 0101
			int8_t a = 5;
			std::string result = std::bitset<8>(a).to_string();
			if (result.back() == '1') return true;
		}

		void save(const char* file, std::vector<int8_t> buffer) { 
			std::ofstream out;
			out.open(file);

			for (unsigned i = 0; i < buffer.size(); i++) out << buffer[i];

			out.close();
		}

		void retriveNsave(ObjectModel::Root* r) {
			int16_t iterator = 0;
			std::vector<int8_t> buffer(r->getSize());
			std::string name = r->getName().substr(0, r->getName().length()).append(".abc");
			r->pack(&buffer, &iterator);
			save(name.c_str(), buffer);
		}
	}

	// encode integral types
	template<typename T>
	void encode(std::vector<int8_t>* buffer, int16_t* iterator, T value) {
		for (unsigned i = 0, j = 0; i < sizeof(T); i++) (*buffer)[(*iterator)++] = value >> (((sizeof(T) * 8) - 8) - (i == 0 ? j : j += 8));
	}

	template<>
	void encode<float>(std::vector<int8_t>* buffer, int16_t* iterator, float value) {
		int32_t result = *reinterpret_cast<int32_t*>(&value);
		encode<int32_t>(buffer, iterator, result);
	}

	template<>
	void encode<double>(std::vector<int8_t>* buffer, int16_t* iterator, double value) {
		int64_t result = *reinterpret_cast<int64_t*>(&value);
		encode<int64_t>(buffer, iterator, result);
	}

	//encode strings
	template<>
	void encode<std::string>(std::vector<int8_t>* buffer, int16_t* iterator, std::string value) {
		for (unsigned i = 0; i < value.size(); i++) encode<int8_t>(buffer, iterator, value[i]);
	}

	//encode arrays
	template<typename T>
	void encode(std::vector<int8_t>* buffer, int16_t* iterator, std::vector<T> value) { 
		for (unsigned i = 0; i < value.size(); i++) encode<T>(buffer, iterator, value[i]);
	}
}

namespace ObjectModel {
	// definition
	Root::Root() : name("unknown"), wrapper(0), nameLength(0), size(sizeof nameLength + sizeof wrapper + sizeof size) {}

	int32_t Root::getSize() {
		return size;
	}

	void Root::setName(std::string name) { 
		this->name = name;
		nameLength = (int16_t)name.length();
		size += nameLength;
	}

	std::string Root::getName() {
		return name;
	}

	void Root::pack(std::vector<int8_t>*, int16_t*) {
		//
	}

	Primitive::Primitive() {
		size += sizeof type;
	}

	void Primitive::pack(std::vector<int8_t>* buffer, int16_t* iterator) {
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<int16_t>(buffer, iterator, nameLength);
		Core::encode<int8_t>(buffer, iterator, wrapper);
		Core::encode<int8_t>(buffer, iterator, type);
		Core::encode<int8_t>(buffer, iterator, *data);
		Core::encode<int32_t>(buffer, iterator, size);
	}

	Array::Array() {
		size += sizeof type + sizeof count;
	}

	void Array::pack(std::vector<int8_t>* buffer, int16_t* iterator) {
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<int16_t>(buffer, iterator, nameLength);
		Core::encode<int8_t>(buffer, iterator, wrapper);
		Core::encode<int8_t>(buffer, iterator, type);
		Core::encode<int32_t>(buffer, iterator, count);
		Core::encode<int8_t>(buffer, iterator, *data);
		Core::encode<int32_t>(buffer, iterator, size);
	}

	Object::Object(std::string name) {
		setName(name);
		wrapper = static_cast<int8_t>(Wrapper::OBJECT);
		size += sizeof count;
	}

	void Object::addEntity(Root* r) {
		this->entities.push_back(r);
		count++;
		size += r->getSize();
	}

	Root* Object::findByName(std::string name) {
		for (auto r : entities) if (r->getName() == name) return r; //Root*
		std::cout << "no as such" << std::endl;
		return new Object("ninja"); //ninja means: object is not found (but here's a ninja).
	}

	void Object::pack(std::vector<int8_t>* buffer, int16_t* iterator) {
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<int16_t>(buffer, iterator, nameLength);
		Core::encode<int8_t>(buffer, iterator, wrapper);
		Core::encode<int16_t>(buffer, iterator, count);

		for (Root* r : entities) r->pack(buffer, iterator);
		Core::encode<int32_t>(buffer, iterator, size);
	}
}


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
		void serialize();
	};

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

	class KeyboardEvent : public Event {
	private:
		int16_t keyCode;
		bool pressed;
		bool released;
	public:
		KeyboardEvent(int16_t, bool, bool);
		~KeyboardEvent();
		void serialize(ObjectModel::Object*);
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
		return active; //there was: if (!system) return false; return true;
	}

	int32_t Event::getID() {
		return ID;
	}

	void System::serialize() {
		ObjectModel::Object system("SysInfo");
		ObjectModel::Array* name = ObjectModel::Array::createString("sysName", ObjectModel::Type::I8, this->name);
		ObjectModel::Primitive* desc = ObjectModel::Primitive::create("desc", ObjectModel::Type::I32, this->descriptor);
		ObjectModel::Primitive* index = ObjectModel::Primitive::create("index", ObjectModel::Type::I16, this->index);
		ObjectModel::Primitive* active = ObjectModel::Primitive::create("active", ObjectModel::Type::BOOL, this->active);
		system.addEntity(name);
		system.addEntity(desc);
		system.addEntity(index);
		system.addEntity(active);

		for (Event* e : events) {
			KeyboardEvent* kb = static_cast<KeyboardEvent*>(e);
			ObjectModel::Object* eventObject = new ObjectModel::Object("Event: " + std::to_string(e->getID()));
			kb->serialize(eventObject);
			system.addEntity(eventObject);
		}
		Core::Util::retriveNsave(&system);
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

	KeyboardEvent::KeyboardEvent(int16_t keyCode, bool pressed, bool released) : Event(Event::DeviceType::KEYBOARD), keyCode(keyCode), pressed(pressed), released(released) {}

	void KeyboardEvent::serialize(ObjectModel::Object* o) {
		Event::serialize(o);
		ObjectModel::Primitive* keyCode = ObjectModel::Primitive::create("keyCode", ObjectModel::Type::I16, this->keyCode);
		ObjectModel::Primitive* pressed = ObjectModel::Primitive::create("pressed", ObjectModel::Type::BOOL, this->pressed);
		ObjectModel::Primitive* released = ObjectModel::Primitive::create("released", ObjectModel::Type::BOOL, this->released);
		o->addEntity(keyCode);
		o->addEntity(pressed);
		o->addEntity(released);		
	}
}

using namespace EventSystem;
using namespace ObjectModel;
using namespace Core;
using namespace Util;

int main(int argc, char** argv) {
	assert(Core::Util::isLittleEndian());

#if 0
	int32_t foo = 5;
	Primitive* p = Primitive::create("int32", ObjectModel::Type::I32, foo);
	Core::Util::retriveNsave(p);
	std::cout << "name: " << p->getName() << "\nsize: " << p->getSize() << std::endl;

	std::vector<int64_t> data { 1, 2, 3 ,4 };
	Array* arr = Array::createArray("array", Type::I64, data);
	retriveNsave(arr);
	
	std::string some = "some str";
	Array* str = Array::createString("string", Type::I8, some);
	retriveNsave(str);

	Object Test("tEST");
	Test.addEntity(p);
	Test.addEntity(arr);
	Test.addEntity(str);

	Object Test2("2tEST");
	Test2.addEntity(p);
	retriveNsave(&Test2);

	Test.addEntity(&Test2);
	retriveNsave(&Test);
#endif

	System Foo("Foo");
	Event* e = new KeyboardEvent('a', true, false);

	Foo.addEvent(e);
	KeyboardEvent* kb = static_cast<KeyboardEvent*>(Foo.getEvent()); //better use this line, than less safe: (Keyboard*)Foo.getEvent();
	
	Foo.serialize();

	(void)argc;
	(void)argv;

	return 0;
}