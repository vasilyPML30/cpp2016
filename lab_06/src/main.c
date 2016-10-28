#include "phonebook.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    srand(time(0));
    phonebook_t book;
    init_phonebook(&book);
    load_phonebook_xml(argv[1], &book);
    print_phonebook(&book);
    gen_phonebook(&book, rand() % 9 + 1);
    save_phonebook_xml(argv[2], &book);
    clear_phonebook(&book);
    return 0;
}
