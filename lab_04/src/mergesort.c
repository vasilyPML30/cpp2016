#include <stdlib.h>
#include "mergesort.h"

void cpy_elem(void *a, void *b, size_t size)
{
	char *first = (char *)a;
	char *second = (char *)b;
	for (size_t i = 0; i < size; ++i)
		first[i] = second[i];
}

int mergesort(void *base, size_t num, size_t size, int (*compar)(const void *,const void *))
{
	if (num <= 1)
		return 0;
	char *array = (char *)base;
	char *copy = (char *)malloc(size * num);
	for (size_t i = 0; i < num * size; ++i)
		copy[i] = array[i];
	int mid = num / 2;
	mergesort(copy, mid, size, compar);
	mergesort(copy + size * mid, num - mid, size, compar);
	size_t a = 0, b = size * mid, c = 0;
	while (1)
	{
		while (a < size * mid && compar(copy + a, copy + b) <= 0)
		{
			cpy_elem(array + c, copy + a, size);
			a += size;
			c += size;
		}
		if (a >= size * mid)
			break;
		while (b < size * num && compar(copy + b, copy + a) <= 0)
		{
			cpy_elem(array + c, copy + b, size);
			b += size;
			c += size;
		}
		if (b >= size * num)
			break;
	}
	while (a < size * mid)
	{
		cpy_elem(array + c, copy + a, size);
		a += size;
		c += size;
	}
	while (b < size * num)
	{
		cpy_elem(array + c, copy + b, size);
		b += size;
		c += size;
	}
	free(copy);
	return 0;
}