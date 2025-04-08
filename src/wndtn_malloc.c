// https://github.com/Winderton/malloc

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#define STACK_SIZE 32
#define HEAP_SIZE STACK_SIZE * 4
#define HEADER 4
#define FREE_LIST_SIZE 40

static uint16_t IN_USE; // = 0; //если указать глобальную переменную статичной, то она автоматически инициализируется нулём.

typedef struct virtual_memory {
	uint8_t stack[STACK_SIZE]; // локальные переменные
	char** unmapped; // неназначенная память
	uint8_t heap[HEAP_SIZE]; // динамическая память

	//дз #2. сделать дефрагментацию.

	struct
	{
		char** data; //инициализированные данные
		char** bss; // неинициализированные данные
		char* text;	//readonly данные
	} data_t;
	
} virtual_memory_t;

typedef struct entity {
	uint8_t* ptr;
	uint16_t size;
} entity_t;

entity_t LIST[FREE_LIST_SIZE];

void LOG() {
	printf("OUR LIST\n");
	for (unsigned i = 0; i < IN_USE; i++) {
		printf("DATA + HEADER. [%p]. Memory of our heap free:[%u]\n", LIST[i].ptr, LIST[i].size);
	}
	printf("Entities in use:[%d]\n", (sizeof(LIST) / sizeof(LIST[0]) - IN_USE));
}

entity_t* new_entity(size_t size) {
	if (LIST[0].ptr == NULL && LIST[0].size == 0) { //инициализация виртуальной памяти.
		static virtual_memory_t vm; //неочищаемая переменная виртаульной памяти.
		LIST[0].ptr = vm.heap;
		LIST[0].size = HEAP_SIZE;
		IN_USE++;
		LOG();
	}

	entity_t* best = LIST;

	for (unsigned i = 0; i < IN_USE; i++) {
		if (LIST[i].size >= size && LIST[i].size < best->size) { //выборка первой попавшейся 
			best = &LIST[i];
		}
	}

	return best;
}

void* w_malloc(size_t size) {
	assert(size + HEADER <= HEAP_SIZE);	//предотвратить превышение выделения памяти.
								// дз от вднтн #1: увеличивать память при превышении, вместо ограничивания.
	size += HEADER;

	entity_t* e = new_entity(size);

	uint8_t* start = e->ptr;
	uint8_t* user_ptr = start + HEADER;

	*start = size;

	e->ptr += size;
	e->size -= size;

	assert(e->size + HEADER >= 0);
	LOG();
	return user_ptr;
}

void w_free(void* ptr) {
	uint8_t* start = (uint8_t*)ptr - HEADER;

	LIST[IN_USE].ptr = &(*start); //start
	LIST[IN_USE].size = (uint8_t)*((uint8_t*)ptr - HEADER); //*start

	IN_USE++;

	LOG();
}

void test() {
	// int* a = w_malloc(sizeof(int));
	// double* b = w_malloc(sizeof(double));

	// w_free(a);

	typedef struct foo {
		int a;
		int b;
	} foo_t;

	foo_t* foo;
	char* bar;
	int* bazz;

	foo = w_malloc(sizeof(foo_t));
	bar = w_malloc(5);
	bazz = w_malloc(sizeof(int));

	foo->a = 5;
	foo->b = 10;

	strcpy(bar, "bar");

	memcpy(bazz, &foo->a, sizeof(int));

	printf("Address: [%p], data: [%d] [%d]\n", foo, foo->a, foo->b);
	printf("Address: [%p], data: [%s]\n", bar, bar);
	printf("Address: [%p], data: [%d]\n", bazz, *bazz);

	w_free(foo);
	w_free(bar);
	//w_free(bazz);

	char* other = w_malloc(4);
	strcpy(other, "other");
	printf("Address: [%p], data: [%s]\n", other, other);

}

int main(void) {
	test();
	return 0;
}