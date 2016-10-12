#include <stdio.h>
#include <string.h>
#include "clist.h"
#include "io.h"

void show_point(struct intrusive_node *i_node, void *format)
{
	struct position_node *node = container_of(i_node, struct position_node, node);
	printf((char *)format, node->x, node->y);
}

void count_point(struct intrusive_node *i_node, void *cnt)
{
	(*(int *)cnt)++;
}

void apply(struct intrusive_list *list, void (*op)(struct intrusive_node *, void *), void *args)
{
	struct intrusive_node *ptr = list->head->next;
	while (ptr != list->head)
	{
		op(ptr, args);
		ptr = ptr->next;
	}
}

int main(int argc, char **argv)
{
	struct intrusive_list list;
	init_list(&list);
	if (strcmp(argv[1], "loadtext") == 0)
		loadtext(&list, argv[2]);
	else if (strcmp(argv[1], "loadbin") == 0)
		loadbin(&list, argv[2]);
	if (strcmp(argv[3], "print") == 0)
	{
		apply(&list, show_point, argv[4]);
		printf("\n");
	}
	else if (strcmp(argv[3], "count") == 0)
	{
		int cnt = 0;
		apply(&list, count_point, &cnt);
		printf("%i\n", cnt);
	}
	else if (strcmp(argv[3], "savetext") == 0)
		savetext(&list, argv[4]);
	else if (strcmp(argv[3], "savebin") == 0)
		savebin(&list, argv[4]);
	destroy_list(&list);
}
