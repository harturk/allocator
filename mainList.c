#include <stdio.h>
#include "list.h"

void view_list(struct list_s *list)
{
	int i = 0;
	struct node_s *node = list->head;

	while (node->next->next)
	{
		node = node->next;
		printf("node %d (%p) -> prev: %p, next: %p, data: %ld\n",
			   i++, node, node->prev, node->next, (long)node->data);
	};
	printf("%d nodes, head: %p, tail %p\n", list->length, list->head, list->tail);
}

struct node_s *cmpfunc(struct node_s *node, void *arg)
{
	int a = (long)node->data;
	int b = (long)arg;

	if (a < b)
		printf("%d < %d\n", a, b);
	else
		printf("%d >= %d\n", a, b);

	return 0;
}

struct node_s *findfunc(struct node_s *node, void *arg)
{
	int a = (long)node->data;
	int b = (long)arg;

	if (a == b)
		return node;
	else
		return 0;
}

int run(void)
{
	struct list_s *lst;
	struct node_s *node;
	int error;

	lst = list_create();

	list_pushback(lst, (void *)123);
	list_pushback(lst, (void *)456);
	list_pushback(lst, (void *)789);
	view_list(lst);

	list_push(lst, (void *)-123);
	list_push(lst, (void *)-456);
	list_push(lst, (void *)-789);
	view_list(lst);

	printf("pop: %ld\n", (long)list_pop(lst));
	printf("pop: %ld\n", (long)list_pop(lst));
	printf("pop: %ld\n", (long)list_pop(lst));
	view_list(lst);
	printf("popback: %ld\n", (long)list_popback(lst));
	printf("popback: %ld\n", (long)list_popback(lst));
	printf("popback: %ld\n", (long)list_popback(lst));
	view_list(lst);

	node = list_push(lst, (void *)222);
	list_insert(lst, lst->head, (void *)1010);
	list_insert(lst, lst->head, (void *)2020);
	list_push(lst, (void *)333);
	list_insert(lst, node, (void *)3030);
	list_insert(lst, lst->tail->prev, (void *)5050);
	view_list(lst);

	list_remove(lst, node);
	view_list(lst);

	printf("[index 0: %p, index 1: %p]\n",
		   list_index(lst, 0), list_index(lst, 1)),
		printf("[index 4: %p, index 3: %p]\n",
			   list_index(lst, -1), list_index(lst, -2));

	list_foreach(lst, cmpfunc, (void *)2500);
	node = list_foreach(lst, findfunc, (void *)3030);
	if (node)
		printf("node %p, data: %ld\n", node, (long)node->data);

	error = list_destroy(lst);
	if (error)
		printf("error destroying list (still full)\n");

	list_pop(lst);
	list_pop(lst);
	list_pop(lst);
	list_pop(lst);
	list_pop(lst);

	error = list_destroy(lst);
	if (!error)
		printf("list destroyed.\n");

	return 0;
}
