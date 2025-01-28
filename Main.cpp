#include "List.h"
#include <iostream>
#include <stdio.h>

int main()
{
	char** test;

	char* text1 = "qwerty123";
	char* text2 = "Hello, world!";

	init(&test);

	add_to(&test, "qwerty");
	add_to(&test, "qwerty1");
	add_to(&test, "qwerty12");
	add_to(&test, text1);
	add_to(&test, "qwerty09");
	add_to(&test, "qwerty0");

	for (int i = 0; i < get_size(test); i++) {
		printf("%s\n", test[i]);
	}

	replace(test, text1, text2);
	std::cout << std::endl;

	for (int i = 0; i < get_size(test); i++) {
		printf("%s\n", test[i]);
	}

	destroy(&test);
}