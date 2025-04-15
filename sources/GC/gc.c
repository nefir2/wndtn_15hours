#include <stdio.h>
#include <stdlib.h>
#include "gc.h"

#define IGCT 8

void push(vm* vm, Object* object) {
	vm->stack[vm->stackSize++] = object;
}

Object* pop(vm* vm) {
	return vm->stack[--vm->stackSize];
}

vm* newVm() {
	vm* mainVm = (vm*)malloc(sizeof(vm));
	mainVm->stackSize = 0;
	mainVm->firstObject = NULL;
	mainVm->numObjects = 0;
	mainVm->maxObjects = IGCT;
	return mainVm;
}

Object* newObject(vm* vm, oType type) {
	if (vm->numObjects == vm->maxObjects) gc(vm);
	Object* object = (Object*)malloc(sizeof(Object));
	object->type = type;
	vm->numObjects++; //очепятка, я так понял, он там прибавляет в максобжектс.
	return object;
}

void pushInt(vm* vm, int intV) {
	Object* object = newObject(vm, INT);
	object->value = intV;
	push(vm, object);
}

void pushTwin(vm* vm) {
	Object* object = newObject(vm, TWIN);
	object->tail = pop(vm);
	object->head = pop(vm);
	push(vm, object);
}

void mark(Object* object) {
	if (object->marked) return;
	object->marked = 1;
	if (object->type == TWIN) {
		mark(object->head);
		mark(object->tail);
	}
}

void markAll(vm* vm) {
	for (int i = 0; i < vm->stackSize; i++) mark(vm->stack[i]);
}

void marksweep(vm* vm) {
	Object** object = &vm->firstObject;
	while (*object) {
		if (!(*object)->head) {
			Object* unreached = *object;
			*object = unreached->next;
			free(unreached);
			vm->numObjects--;
		}
		else {
			(*object)->marked = 0;
			object = &(*object)->next;
		}
	}
}

void gc(vm* vm) {
	int numObjects = vm->numObjects;
	markAll(vm);
	marksweep(vm);
	vm->maxObjects = vm->numObjects * 2; //после очистки увеличить максимальное количество объектов.
}

void freeVm(vm* vm) {
	vm->stackSize = 0;
	gc(vm);
	free(vm);
}

void printObj(Object* object) {
	switch (object->type)
	{
		case INT:
			printf("typeint: %d\n", object->value);
			break;

		case TWIN:
			printf("typetwin: (");
			printObj(object->head);
			printf(", ");
			printObj(object->tail);
			printf(")\n");
			break;
		
		default:
			break;
	}
}