#pragma once
#include "root.h"

namespace ObjectModel
{
	class LIB Array : public Root {
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
} // namespace ObjectModel
