// #include <iostream>
// #include <vector>
// #include <bitset>
// #include <assert.h>
// #include <fstream>
// #include <random>
// #include <string>

#include "eventsystem.h"
#include <serialization.h>
#include <cassert>

using namespace EventSystem;
using namespace ObjectModel;
using namespace Core::Util;

int main(int argc, char** argv) {
	assert(Core::Util::isLittleEndian());

#if 0
	int32_t foo = 5;
	Primitive* p = Primitive::create("int32", ObjectModel::Type::I32, foo);
	Core::Util::retriveNsave(p);
	//std::cout << "name: " << p->getName() << "\nsize: " << p->getSize() << std::endl;

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

#if 0
	System Foo("Foo");
	Event* e = new KeyboardEvent('a', true, false);

	Foo.addEvent(e);
	KeyboardEvent* kb = static_cast<KeyboardEvent*>(Foo.getEvent()); //better use this line, than less safe: (Keyboard*)Foo.getEvent();
	
	Foo.serialize();
#endif

	int16_t testable = 23;
	Primitive* p = Primitive::create("int16", Type::I16, testable);
	retriveNsave(p);

	std::vector<int8_t> result = Core::Util::load("int16.abc");
	printf("loaded from file value:\n");
	for (unsigned i = 0; i < result.size(); i++) printf("%02X ", result[i]);
	printf("\n");
	for (unsigned i = 0; i < result.size(); i++) printf("%с ", result[i]);
	printf("\n");

	(void)argc;
	(void)argv;

	return 0;
}