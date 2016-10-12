#include "io.h"
#include "clist.h"

void loadtext(struct intrusive_list *list, char *fname)
{
	FILE *infile = fopen(fname, "rt");
	int x, y;
	while (fscanf(infile, "%i%i", &x, &y) != EOF)
		add_position(list, x, y);
	fclose(infile);
}

void loadbin(struct intrusive_list *list, char *fname)
{
	FILE *infile = fopen(fname, "rb");
	int x = 0, y = 0;
	while (fread((void *)&x, 3, 1, infile) && fread((void *)&y, 3, 1, infile))
	{
		if (x & (1 << 23))
			x |= (255 << 24);
		if (y & (1 << 23))
			y |= (255 << 24);
		add_position(list, x, y);
		x = y = 0;
	}
	fclose(infile);
}

void savetext(struct intrusive_list *list, char *fname)
{
	FILE *outfile = fopen(fname, "wt");
	struct intrusive_node *ptr = list->head->next;
	while (ptr != list->head)
	{
		struct position_node *node = container_of(ptr, struct position_node, node);
		fprintf(outfile, "%i %i\n", node->x, node->y);
		ptr = ptr->next;
	}
	fclose(outfile);
}

void savebin(struct intrusive_list *list, char *fname)
{
	FILE *outfile = fopen(fname, "wb");
	struct intrusive_node *ptr = list->head->next;
	while (ptr != list->head)
	{
		struct position_node *node = container_of(ptr, struct position_node, node);
		int x = node->x;
		int y = node->y;
		fwrite((void *)&x, 3, 1, outfile);
		fwrite((void *)&y, 3, 1, outfile);
		ptr = ptr->next;
	}
	fclose(outfile);
}
