#include <stdio.h>
#include <string.h>
#include "clist.h"

void add_position(struct intrusive_list *list, int x, int y)
{
	struct position_node *new_node = malloc(sizeof(struct position_node));
	new_node->x = x;
	new_node->y = y;
	add_node(list, &new_node->node);
}

void show_all_positions(struct intrusive_list *list)
{
	struct intrusive_node *ptr = list->head->next;
	while (ptr != list->head)
	{
		struct position_node *val_ptr = container_of(ptr, struct position_node, node);
		printf("(%i %i) ", val_ptr->x, val_ptr->y);
		ptr = ptr->next;
	}
	printf("\n");
}


void remove_position(struct intrusive_list *list, int x, int y)
{
	struct intrusive_node *ptr = list->head->next, *tmp;
	while (ptr != list->head)
	{
		struct position_node *val_ptr = container_of(ptr, struct position_node, node);
		tmp = ptr->next;
		if (val_ptr->x == x && val_ptr->y == y)
			remove_node(list, ptr);
		ptr = tmp;
	}
}


int main()
{
	static char cmd[30];
	struct intrusive_list list;
	init_list(&list);
	while (1)
	{
		scanf("%s", cmd);
		if (strcmp(cmd, "exit") == 0)
			break;
		else if (strcmp(cmd, "len") == 0)
			printf("%i\n", get_length(&list));
		else if (strcmp(cmd, "rma") == 0)
			remove_all_positions(&list);
		else if (strcmp(cmd, "print") == 0)
			show_all_positions(&list);
		else if (strcmp(cmd, "rm") == 0)
		{
			int x, y;
			scanf("%i %i", &x, &y);
			remove_position(&list, x, y);
		}
		else if (strcmp(cmd, "add") == 0)	
		{
			int x, y;
			scanf("%i %i", &x, &y);
			add_position(&list, x, y);
		}
		else
			printf("Unknown command\n");
	}
	destroy_list(&list);
}
