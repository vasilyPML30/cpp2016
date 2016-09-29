#include "clist.h"

void add_node(struct intrusive_list *list, struct intrusive_node *new_node)
{
	new_node->prev = list->head;
	new_node->next = list->head->next;
	new_node->next->prev = new_node;
	list->head->next = new_node;
}

void init_list(struct intrusive_list *list)
{
	list->head = malloc(sizeof(struct intrusive_node));
	list->head->prev = list->head->next = list->head;
}

void remove_node(struct intrusive_list *list, struct intrusive_node *node)
{
	struct position_node *ptr = container_of(node, struct position_node, node);
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(ptr);
}

void remove_all_positions(struct intrusive_list *list)
{
	struct intrusive_node *ptr = list->head->next, *tmp;
	while (ptr != list->head)
	{
		tmp = ptr->next;
		remove_node(list, ptr);
		ptr = tmp;
	}
}

void destroy_list(struct intrusive_list *list)
{
	remove_all_positions(list);
	free(list->head);
}

int get_length(struct intrusive_list *list)
{
	int cnt = 0;
	struct intrusive_node *ptr = list->head->next;
	while (ptr != list->head)
	{
		ptr = ptr->next;
		cnt++;
	}
	return cnt;
}