#define STACK_MAX_SIZE 256

typedef enum { INT, TWIN } oType;
typedef struct sObject {
	oType type;
	unsigned char marked;
	struct sObject* next;
	union {
		int value;
		struct {
			struct sObject* head;
			struct sObject* tail; //он написал "tile"
		};
	};
} Object;
typedef struct {
	Object* stack[STACK_MAX_SIZE];
	int stackSize;
	Object* firstObject;
	int numObjects;
	int maxObjects;
} vm;

void push(vm*, Object*);
Object* pop(vm*);

vm* newVm();

Object* newObject(vm*, oType);

void pushInt(vm*, int);
void pushTwin(vm*);

void mark(Object*);
void markAll(vm*);
void marksweep(vm*);
void gc(vm*);
void freeVm(vm*);
void printObj(Object*);