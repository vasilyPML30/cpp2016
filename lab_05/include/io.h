#ifndef _IO_H_
#define _IO_H_

#include <stdio.h>
#include "clist.h"

void loadtext(struct intrusive_list *list, char *fname);
void loadbin(struct intrusive_list *list, char *fname);
void savetext(struct intrusive_list *list, char *fname);
void savebin(struct intrusive_list *list, char *fname);

#endif