#include <stdio.h>
#include "str.h"

int Check(const char * str1, const char *str2)
{
	while (*str1 != 0)
	{
		if (*str1 != *str2)
			return 0;
		str1++;
		str2++;
	}
	return 1;
}

void test_cpy()
{
	char arr[100];
	char *dest = arr;
	char tests[5][100] =
	{
		"a",
		"",
		{'a', 's', 'd'},
		{},
		"sdfghjkjhgfdsdfghjkjhgf"
	};
	printf("testing strcpy:\n");
	for (int i = 0; i < 5; ++i)
	{
		printf("  \"%s\": ", tests[i]);
		dest = strcpy(dest, tests[i]);
		printf(Check(dest, tests[i]) == 1 ? "OK\n" : "FAILED\n");
	}
}

void test_cat()
{
	char *dest;
	char tests[10][100] =
	{
		"abc", "def",
		"123", "456",
		"asdf", "",
		"", "qwer",
		"", ""
	};
	char answers[5][100] = {"abcdef", "123456", "asdf", "qwer", ""};
	printf("testing strcat:\n");
	for (int i = 0; i < 5; ++i)
	{
		printf("  \"%s\" + \"%s\": ", tests[2 * i], tests[2 * i + 1]);
		dest = tests[2 * i];
		dest = strcat(dest, tests[2 * i + 1]);
		printf(Check(dest, answers[i]) == 1 ? "OK\n" : "FAILED\n");
	}
}

void test_cmp()
{
	char tests[16][100] =
	{
		"abcd", "abcd",
		"abce", "abcd",
		"abce", "abcz",
		"abcd", "abc",
		"abcd", "abcde",
		"a", "",
		"", "a",
		"", ""
	};
	int answers[] = {0, 1, -1, 1, -1, 1, -1, 0};
	printf("testing strcmp:\n");
	for (int i = 0; i < 8; ++i)
	{
		printf("  \"%s\" ? \"%s\": ", tests[2 * i], tests[2 * i + 1]);
		printf(strcmp(tests[2 * i], tests[2 * i + 1]) == answers[i] ? "OK\n" : "FAILED\n");
	}
}

void test_len()
{
	char tests[5][100] = {"", "a", "ab", "abc", "asdfghjkl"};
	int answers[] = {0, 1, 2, 3, 9};
	printf("testing strlen:\n");
	for (int i = 0; i < 5; ++i)
	{
		printf("  \"%s\": ", tests[i]);
		printf(strlen(tests[i]) == answers[i] ? "OK\n" : "FAILED\n");
	}}
