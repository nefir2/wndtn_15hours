#pragma once
#include <stdint.h>

namespace ObjectModel
{
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

	template<typename ...>
	uint8_t getTypeSize(Type type) {
		switch (type) {
			case Type::BOOL:	return sizeof(bool);		break;
			case Type::I8:		return sizeof(uint8_t);		break;
			case Type::I16:		return sizeof(uint16_t);	break;
			case Type::I32:		return sizeof(uint32_t);	break;
			case Type::I64:		return sizeof(uint64_t);	break;
			case Type::FLOAT:	return sizeof(float);		break;
			case Type::DOUBLE: 	return sizeof(double);		break;
		}
	}
}
