#include "List.h"

#ifdef _WIN32
#define SIZE(block) _msize(block)
#elif __linux__
#define SIZE(block) malloc_usable_size(block)
#endif // CHECK OS


void init(char*** list) {
	*list = (char**)malloc(sizeof(char*));
	if (*list != nullptr)
		(*list)[0] = nullptr;
}
void destroy(char*** list) {
	if (*list != nullptr) {
		auto size = get_size(*list);

		for (unsigned long long i = 0; i < size; i++) {
			if ((*list)[i] != nullptr) {
				free((*list)[i]);
			}
		}

		free(*list);
		*list = nullptr;
	}
}

void add_to(char*** list, char* str) {
	if (str != nullptr) {
		unsigned long long size = get_size(*list);

		if (size == 0) {
			(*list)[size] = (char*)malloc((strlen(str) + 1));
			memcpy((*list)[size], str, strlen(str) + 1);
		}
		else {
			char** buff = (char**)realloc(*list, (size + 1) * sizeof(char*));
			if (buff != nullptr) {
				*list = buff;

				(*list)[size] = (char*)malloc((strlen(str) + 1));
				if ((*list)[size] != nullptr)
					memcpy((*list)[size], str, strlen(str) + 1);

			}
		}
	}
}
void delete_from(char** list, char* str) {
	unsigned long long size = get_size(list);
	if (list != nullptr) {
		if (size > 1) {
			unsigned long long deleted = 0;

			for (unsigned long long i = 0; i < size; i++) {
				if (strcmp(list[i], str) == 0) {
					free(list[i]);
					list[i] = nullptr;
					deleted++;
				}
			}

			for (unsigned long long i = 0; i < deleted; i++) {
				for (unsigned long long j = 0; j < size; j++) {
					if (list[j] == nullptr) {
						list[j] = list[j + 1];
						list[j + 1] = nullptr;
					}
				}
			}

			char** buff = (char**)realloc(list, (size - deleted) * sizeof(char*));
			if (buff != nullptr) {
				list = buff;
			}
		}
		else if (size == 1) {
			free(list[0]);
			list[0] = nullptr;
		}
	}
}

unsigned long long get_size(char** list) {
	if (list != nullptr)
		return list[0] != nullptr ? SIZE(list) / sizeof(list[0]) : 0;
	return 0;
}

unsigned long long find_first(char** list, char* str) {
	if (str != nullptr && list != nullptr) {
		unsigned long long size = get_size(list);
		for (unsigned long long i = 0; i < size; i++) {
			if (list[i] != nullptr && strcmp(list[i], str) == 0) {
				return i;
			}
		}
	}

	return -1;
}

void make_distinct(char*** list) {
	if (*list != nullptr) {
		/*unsigned long long index = 0, deleted = 0, size = get_size(list);

		for (unsigned long long i = size; i > 0; i--) {
			index = find_first(list, list[i - 1]);

			while (index != i - 1 && list[i-1] != nullptr) {
				if (index == unsigned long long{} - 1) {
					break;
				}

				if (index == 0 && index != i-1) {
					free(list[i - 1]);
					list[i - 1] = nullptr;
				}
				else if (index != 0) {
					free(list[index]);
					list[index] = nullptr;
				}

				deleted++;
				index = find_first(list, list[i - 1]);
			}
		}

		for (unsigned long long i = 0; i < deleted; i++) {
			for (unsigned long long j = 0; j < size; j++) {
				if (list[j] == nullptr) {
					list[j] = list[j + 1];
					list[j + 1] = nullptr;
				}
			}
		}*/

		/*char** buff = (char**)realloc(list, (size - deleted) * sizeof(char*));
		if (buff != nullptr) {
			list = buff;
		}*/

		char** copy;
		init(&copy);


		unsigned long long size = get_size(*list), count = 0;
		add_to(&copy, (*list)[0]);

		for (unsigned long long i = 1; i < size; i++) {
			for (unsigned long long j = 0; j < get_size(copy); j++) {
				if (strcmp(copy[j], (*list)[i]) != 0) {
					count++;
				}
			}
			if (count == get_size(copy)) {
				add_to(&copy, (*list)[i]);
			}
			count = 0;
		}

		if (get_size(copy) != size) {
			destroy(&(*list));
			*list = copy;
		}
	}
}

void replace(char** list, char* before, char* after) {
	if (before != nullptr && after != nullptr && list != nullptr) {
		unsigned long long size = get_size(list);
		for (unsigned long long i = 0; i < size; i++) {
			if (strcmp(list[i], before) == 0) {
				char* buff = (char*)realloc(list[i], strlen(after)+1);
				if (buff != nullptr)
					list[i] = buff;
				memcpy(list[i], after, strlen(after) + 1);
			}
		}
	}
}

void sort_ascending(char** list) {
	if (list != nullptr) {
		unsigned long long size = get_size(list);
		for (unsigned long long j = 0; j < size; j++) {
			for (unsigned long long i = 0; i < size - 1; i++) {
				if (strlen(list[i]) > strlen(list[i+1])) {
					char* buff = list[i + 1];
					list[i + 1] = list[i];
					list[i] = buff;
				}
			}
		}
	}
}
