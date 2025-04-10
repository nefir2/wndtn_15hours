#include <iostream>

int main(int argc, char** argv) {
	uint32_t x = 0x12345678;
	std::cout << "x: " << x << std::endl;
	uint8_t* ptr = (uint8_t*)&x;
	printf("mladshiy bayt: 0x%02X\n", ptr[0]);
}