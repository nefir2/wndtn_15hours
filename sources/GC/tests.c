#include <stdio.h>
#include "gc.h"

void first_test() {
	printf("1: объекты на стеке сохранены.\n");
	vm* mainVm = newVm();
	pushInt(mainVm, 1);
	pushInt(mainVm, 2);

	gc(mainVm);
	freeVm(mainVm);
}

void second_test() {
	printf("2: недосягаемые объекты удалены.\n");
	vm* mainVm = newVm();
	pushInt(mainVm, 1);
	pushInt(mainVm, 2);
	pop(mainVm);
	pop(mainVm);

	gc(mainVm);
	freeVm(mainVm);
}

void third_test() {
	printf("3: дотянуться до вложенных объектов.\n");
	vm* mainVm = newVm();
	pushInt(mainVm, 1);
	pushInt(mainVm, 2);
	pushTwin(mainVm);
	pushInt(mainVm, 3);
	pushInt(mainVm, 4);
	pushTwin(mainVm);
	pushTwin(mainVm);

	gc(mainVm);
	freeVm(mainVm);
}

// void fourth_test() {