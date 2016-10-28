#include "phonebook.h"
#include "names.h"
#include <expat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 100000

void push_back_human(phonebook_t *book, human_t *human)
{
	if (book->size >= book->capacity)
	{
		book->capacity = (book->capacity * 2) + 1;
		book->humans = (human_t *)realloc(book->humans, sizeof(human_t) * book->capacity);
	}
	book->humans[book->size++] = *human;
}

void clear_phonebook(phonebook_t *book)
{
	if (book->humans != NULL)
	{
		free(book->humans);
		book->humans = NULL;
	}
	book->size = book->capacity = 0;
}

void print_phonebook(phonebook_t *book)
{
	printf("%lu\n", book->size);
	for (int i = 0; i < book->size; i++)
	{
		printf("name: %s\n", book->humans[i].name);
		printf("middle name: %s\n", book->humans[i].middle_name);
		printf("family name: %s\n", book->humans[i].family_name);
		for (int j = 0; j < book->humans[i].phones_cnt; j++)
			printf("phone: %s\n", book->humans[i].phones[j]);
		printf("\n");
	}
}

int cmpfunc(const void *a, const void *b)
{
	return strcmp(((human_t *)a)->family_name, ((human_t *)b)->family_name);
}

void gen_phonebook(phonebook_t *book, size_t size)
{
	clear_phonebook(book);
	for (int i = 0; i < size; i++)
	{
		human_t human;
		strcpy(human.name, kNames[rand() % NAMES_CNT]);
		strcpy(human.middle_name, kMiddleNames[rand() % MIDDLE_NAMES_CNT]);
		strcpy(human.family_name, kFamilyNames[rand() % FAMILY_NAMES_CNT]);
		human.phones_cnt = rand() % 9 + 1;
		for (int j = 0; j < human.phones_cnt; j++)
		{
			human.phones[j][0] = rand() % 9 + 1 + '0';
			for (int k = 1; k < 20; k++)
				human.phones[j][k] = rand() % 10 + '0';
			human.phones[j][20] = 0;
		}
		push_back_human(book, &human);
	}
	qsort(book->humans, size, sizeof(human_t), cmpfunc);
}

void init_phonebook(phonebook_t *book)
{
	book->humans = NULL;
	book->size = book->capacity = 0;
}

int save_phonebook_xml(const char *filename, phonebook_t *book)
{
	FILE *fp = fopen(filename, "wt");
    if (fp == NULL)
        return 1;
	fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<phonebook>\n");
	for (int i = 0; i < book->size; i++)
	{
		fprintf(fp, "    <human name=\"%s %s %s\">\n", book->humans[i].name, book->humans[i].middle_name, book->humans[i].family_name);
		for (int j = 0; j < book->humans[i].phones_cnt; j++)
			fprintf(fp, "        <phone>%s</phone>\n", book->humans[i].phones[j]);
		fprintf(fp, "    </human>\n");
	}
	fprintf(fp, "</phonebook>");
	fclose(fp);
	return 0;
}

void start_element(void *st, const char *element, const char **attribute)
{
	char *name_str = malloc(100 * sizeof(char));
	state_t *state = (state_t *)st;
	if (strcmp(element, "phonebook") == 0)
		state->type = PHONEBOOK;
	else if (strcmp(element, "human") == 0)
		state->type = HUMAN;
	else if (strcmp(element, "phone") == 0)
		state->type = PHONE;
	if (state->type == HUMAN)
	{
		human_t human;
		human.phones_cnt = 0;
		strcpy(name_str, attribute[1]);
		char *pch = strtok(name_str, " ");
		strcpy(human.name, pch);
		pch = strtok(NULL, " ");
		strcpy(human.middle_name, pch);
		pch = strtok(NULL, " ");
		strcpy(human.family_name, pch);
		push_back_human(state->book, &human);
	}
	else if (state->type == PHONE)
		memset(state->phone, 0, 21);
	free(name_str);
}

void end_element(void *st, const char *element)
{
	state_t *state = (state_t *)st;
	if (strcmp(element, "phonebook") == 0)
		state->type = NONE;
	else if (strcmp(element, "human") == 0)
		state->type = PHONEBOOK;
	else if (strcmp(element, "phone") == 0)
	{
		state->type = HUMAN;
		human_t *human = &state->book->humans[state->book->size - 1];
		strcpy(human->phones[human->phones_cnt++], state->phone);
	}
}

void handle_data(void *st, const char *content, int length)
{
	state_t *state = (state_t *)st;
	char buff[255];
	strncpy(buff, content, length);
	buff[length] = 0;
	if (state->type == PHONE)
	{
		strcat(state->phone, buff);
	}
}

int load_phonebook_xml(const char *filename, phonebook_t *book)
{
	clear_phonebook(book);
	state_t state;
	state.book = book;
	state.type = NONE;
    FILE *fp;
    fp = fopen(filename, "rb");
    if (fp == NULL)
        return 1;
    XML_Parser  parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element, end_element);
    XML_SetCharacterDataHandler(parser, handle_data);
	XML_SetUserData(parser, (void *)&state);
 	char *buff = malloc(BUFFER_SIZE + 1);
	memset(buff, 0, BUFFER_SIZE);
    size_t len = 0;
    int done = 0;
    do {
        len = fread(buff, sizeof(char), BUFFER_SIZE, fp);
        done = len < BUFFER_SIZE;
        if (XML_Parse(parser, buff, len, done) == XML_STATUS_ERROR)
            return 2;
    } while (!done);
    XML_ParserFree(parser);
    fclose(fp);
	free(buff);
    return 0;
}
