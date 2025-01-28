#pragma once
#include <stdlib.h>
#include <string.h>

void init(char***);
void destroy(char***);

void add_to(char*** list, char* str);
void delete_from(char** list,char* str);

unsigned long long get_size(char**);

unsigned long long find_first(char** list, char* str);

void make_distinct(char***);

void replace(char** list, char* before, char* after);

void sort_ascending(char** list);
