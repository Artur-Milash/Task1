#pragma once
#include <stdlib.h>
#include <string.h>

//Simple library to deal with C-style vector (list) of strings

//initialize string list
void init(char***);
//deallocate memory of list
void destroy(char***);

//add string to list
void add_to(char*** list, char* str);
//delete string from list
void delete_from(char** list,char* str);

//get amount of elements in list
unsigned long long get_size(char**);

//find first occurrence of string
unsigned long long find_first(char** list, char* str);

//remove duplicates
void make_distinct(char***);

//replace string (before) with string (after) in list
void replace(char** list, char* before, char* after);

//bubble sorting the list
void sort_ascending(char** list);
