#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mergesort.h"

int cmp_i(const void *l, const void *r)
{
	const int *a = l;
	const int *b = r;
	return *a - *b;
}

int cmp_c(const void *l, const void *r)
{
	const char *a = l;
	const char *b = r;
	return *a - *b;
}

int cmp_str	(const void *l, const void *r)
{
	char* const *a = l;
	char* const *b = r;
	return strcmp(*a, *b);
}


int str_to_int(char *str)
{
	int num = 0, sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str)
		num = num * 10 + *str++ - '0';
	return sign * num;
}

int main(int argc, char **argv)
{
	if (strcmp(argv[1], "int") == 0)
	{
		int *arr = (int *)malloc(sizeof(int) * argc);
		for (int i = 0; i < argc - 2; ++i)
			arr[i] = str_to_int(argv[i + 2]);
		mergesort(arr, argc - 2, sizeof(int), cmp_i);
		for (int i = 0; i < argc - 2; ++i)
			printf("%i ", arr[i]);
		printf("\n");
		free(arr);
	}
	else if (strcmp(argv[1], "char") == 0)
	{
		char *arr = (char *)malloc(sizeof(char) * argc);
		for (int i = 0; i < argc - 2; ++i)
			arr[i] = *argv[i + 2];
		mergesort(arr, argc - 2, sizeof(char), cmp_c);
		for (int i = 0; i < argc - 2; ++i)
			printf("%c ", arr[i]);
		printf("\n");
		free(arr);
	}
	else if (strcmp(argv[1], "str") == 0)
	{
		mergesort(argv + 2, argc - 2, sizeof(char *), cmp_str);
		for (int i = 2; i < argc; ++i)
			printf("%s ", argv[i]);
		printf("\n");
	}
	return 0;
}