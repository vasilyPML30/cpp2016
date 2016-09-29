#include <stddef.h>
#include <stdlib.h>
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))


struct intrusive_node
{
	struct intrusive_node *next;
	struct intrusive_node *prev;
};

struct intrusive_list
{
	struct intrusive_node *head;
};

struct position_node
{
	int x, y;
	struct intrusive_node node;
};

void init_list(struct intrusive_list *list);
void destroy_list(struct intrusive_list *list);
void add_node(struct intrusive_list *list, struct intrusive_node *new_node);
void remove_node(struct intrusive_list *list, struct intrusive_node *node);
int get_length(struct intrusive_list *list);
void remove_all_positions(struct intrusive_list *list);
