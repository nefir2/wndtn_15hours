#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct w_string {
	uint8_t* data;
	uint8_t length;
	uint8_t how_much;
} str_t;

str_t* string_create(uint8_t length) {
	str_t* string = (str_t*)malloc(sizeof(str_t));
	string->data = (uint8_t*)malloc(length);
	string->length = length;
	string->how_much = 0;
	return string;
}

void string_free(str_t* string) {
	free(string->data);
	free(string);
}

uint8_t string_length(str_t* string) {
	return string->length;
}

void print_string(str_t* string, FILE* file) {
	fwrite(string->data, sizeof(uint8_t), string->length, file);
}

size_t wstrlen(const char* string) {
	size_t length = 0;
	while (*string != '\0') {
		length++;
		string++;
	}
	return length;
}

str_t* string_dup(const char* str) {
	str_t* string = string_create((uint8_t)wstrlen(str));
	memcpy(string->data, str, string->length); //задание самому себе: попробовать сделать, как и сделан wstrlen(), функцию wmemcpy(). (если это конечно не капец как сложно.)
	string->how_much = string->length;
	return string;
}

str_t* string_concat(str_t* left, str_t* right) {
	str_t* string = string_create(left->length + right->length);
	memcpy(string->data, left->data, left->length);
	memcpy(string->data + left->length, right->data, right->length);
	string->how_much = string->length;

	return string;
}

int main(int argc, char** argv) {
	//str_t* newline = string_dup("\n");

	str_t* str = string_dup("some string.");
	print_string(str, stdout);
	fprintf(stdout, "\nlength: [%d]\n", string_length(str));

	str_t* concatenated = string_concat(str, str);
	print_string(concatenated, stdout);
	fprintf(stdout, "\nconc length: [%d]\n", string_length(concatenated));

	string_free(str);
	string_free(concatenated);

	return 0;
}