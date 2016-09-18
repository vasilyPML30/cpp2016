#include <stddef.h>

char * strcpy(char * destination, const char * source)
{
	const char * s_pointer = source;
	char * d_pointer = destination;
	while (*s_pointer != 0)
		*(d_pointer++) = *(s_pointer++);
	*d_pointer = 0;
	return destination;
}

char * strcat(char * destination, const char * source)
{
	const char * s_pointer = source;
	char * d_pointer = destination;
	while (*d_pointer != 0)
		d_pointer++;
	while (*s_pointer != 0)
		*(d_pointer++) = *(s_pointer++);
	*d_pointer = 0;
	return destination;
}

int strcmp(const char * str1, const char * str2)
{
	while (*str1 != 0 && *str2 != 0)
	{
		if (*str1 > *str2)
			return 1;
		else if (*str1 < *str2)
			return -1;
		str1++;
		str2++;
	}
	if (*str1 > 0)
		return 1;
	if (*str2 > 0)
		return -1;	
	return 0;
}

size_t strlen(const char * str)
{
	size_t len = 0;
	while (*str != 0)
	{
		len++;
		str++;
	}
	return len;
}
