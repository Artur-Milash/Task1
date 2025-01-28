#include <gtest/gtest.h>
#include "List.h"
#include <string>
#include <unordered_set>

TEST(StringList, Init_Destroy) {
	char** test;
	init(&test);
	ASSERT_NE(test, nullptr);
	destroy(&test);
	ASSERT_EQ(test, nullptr);
}

TEST(StringList, Add_new_string) {
	char** test;
	char str[] = "Hello, world!";

	init(&test);
	add_to(&test, str);

	std::string buff1{ test[0] };
	std::string buff2{ str };

	EXPECT_EQ(buff1, buff2);

	destroy(&test);
}

TEST(StringList, Add_multiple_new_strings) {
	char** test;
	init(&test);

	for (int i = 0; i < 10; i++) {
		char* text = new char[15];
		sprintf(text, "Hello%i", i);
		add_to(&test, text);
		delete[] text;
	}

	EXPECT_EQ(get_size(test), 10);

	destroy(&test);
}

TEST(StringList, Delete_strings) {
	char** test;
	init(&test);

	for (int i = 0; i < 10; i++) {
		char* text = new char[15];
		sprintf(text, "Hello%i", i);
		add_to(&test, text);
		add_to(&test, text);
		delete[] text;
	}

	auto size = get_size(test);

	delete_from(test, "Hello2");
	EXPECT_NE(size, get_size(test));

	size = get_size(test);
	for (std::size_t i = 0; i < size; i++) {
		EXPECT_NE(test[i], nullptr);
	}

	destroy(&test);
}

TEST(StringList, Delete_all_strings) {
	char** test;
	init(&test);

	for (int i = 0; i < 10; i++) {
		char* text = new char[15];
		sprintf(text, "Hello%i", i);
		add_to(&test, text);
		delete[] text;
	}

	while (get_size(test) != 0) {
		delete_from(test, test[0]);
	}

	EXPECT_EQ(test[0], nullptr);

	destroy(&test);
}

TEST(StringList, Find_string) {
	char** test;
	init(&test);

	char* text = new char[15];

	for (int i = 0; i < 10; i++) {
		sprintf(text, "Hello%i", i);
		add_to(&test, text);
	}

	auto index = find_first(test, text);
	EXPECT_EQ(strcmp(test[index], text), 0);

	destroy(&test);
	delete[] text;
}

TEST(StringList, Make_distinct_list) {
	char** test;
	init(&test);

	for (int i = 0; i < 10; i++) {
		char* text = new char[15];
		sprintf(text, "Hello%i", i);
		add_to(&test, text);
		add_to(&test, text);
		delete[] text;
	}

	std::unordered_set<std::string> set;
	auto size = get_size(test);
	for (std::size_t i = 0; i < size; i++) {
		set.emplace(std::string{ test[i] });
	}

	make_distinct(&test);

	size = get_size(test);

	auto begin = set.begin();

	for (std::size_t i = 0; i < size; i++) {
		EXPECT_EQ(strcmp(begin->c_str(), test[i]), 0);
		if (begin == set.end()-- && i != size - 1) {
			ADD_FAILURE();
			break;
		}
		else
			begin++;
	}

	destroy(&test);
}

TEST(StringList, Replace_strings) {
	char** test;
	init(&test);

	char* text = new char[15];

	for (int i = 0; i < 10; i++) {
		sprintf(text, "Hello%i", i);
		add_to(&test, text);
	}

	char text2[] = "Hello, world!";
	auto index = find_first(test, text);
	replace(test, text, text2);

	EXPECT_EQ(strcmp(test[index], text2), 0);

	destroy(&test);
	delete[] text;
}

TEST(StringList, Sort_strings) {
	char** test;
	init(&test);

	for (int i = 0; i < 5; i++) {
		char* text = new char[15];
		sprintf(text, "Hello");
		for (int j = 0; j < i; j++)
			sprintf(text, "%s%i", text, j);
		add_to(&test, text);
		delete[] text;
	}

	auto size = get_size(test);
	sort_ascending(test);

	for (std::size_t i = 0; i < size-1; i++) {
		EXPECT_LT(strlen(test[i]), strlen(test[i+1]));
	}

	destroy(&test);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}