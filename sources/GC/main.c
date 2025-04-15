#include "tests.c"
#include <locale.h>

//https://www.youtube.com/watch?v=9sV949yysb4
//https://github.com/Winderton/GC/

int main(int argc, char** argv) {
	setlocale(LC_ALL, "");
	first_test();
	second_test();
	third_test();
	return 0;
}