#ifndef _PHONEBOOK_H_
#define _PHONEBOOK_H_

#include <stddef.h>

typedef struct human_s
{
    char name[256];
    char middle_name[256];
    char family_name[256];
    char phones[10][21];
    int phones_cnt;
} human_t;	

typedef struct phonebook_s
{
    human_t *humans;
    size_t size;
    size_t capacity;
} phonebook_t;

enum Tag
{
    NONE,
    PHONEBOOK,
    HUMAN,
    PHONE
};

typedef struct state_s
{
    phonebook_t *book;
    char phone[21];
    enum Tag type;
} state_t;

void clear_phonebook(phonebook_t *book);
int load_phonebook_xml(const char *filename, phonebook_t *book);
int save_phonebook_xml(const char *filename, phonebook_t *book);
void print_phonebook(phonebook_t *book);
void init_phonebook(phonebook_t *book);
void gen_phonebook(phonebook_t *book, size_t size);
void push_back_human(phonebook_t *book, human_t *human);

#endif
