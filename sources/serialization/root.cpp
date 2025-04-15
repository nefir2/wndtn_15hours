#include "root.h"

namespace ObjectModel
{
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
		// абстрактный упаковщик
	}
} // namespace ObjectModel
