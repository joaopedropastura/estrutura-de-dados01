#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	char *name;
	int rg;
} UserData;

typedef struct Node
{
	struct Node *next;
	struct Node *prev;
	UserData data;
} Node;

typedef struct LinkedList
{
	Node *head;
	Node *tail;
	size_t length;

} LinkedList;

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void insert_node(LinkedList *list, UserData data, int flag)
{
	Node *newNode = (Node *)malloc(sizeof(Node));

	if (!newNode)
	{
		printf("erro ao alocar memoria\n");
		exit(1);
	}
	if(list->length == 0)
	{
		newNode->prev = NULL;
		newNode->data = data;
		newNode->next = NULL;
		list->tail = newNode;
		list->head = newNode;
	}
	else
	{
		if(flag == 0)
		{
			newNode->prev = NULL;
			newNode->data = data;
			newNode->next = list->head;
			list->head = newNode;
		}
		if(flag == -1)
		{
			list->tail->next = newNode;
			newNode->prev = list->tail;
			newNode->data = data;
			newNode->next = NULL;
			list->tail = newNode;
		}
	}
	// free(newNode);
	list->length++;
}

void delete_node(LinkedList *list, int flag)
{
	if(flag == 0)
		list->head = list->head->next;
	if(flag == -1)
	{
		list->tail = list->tail->prev;
		list->tail->next = NULL;
	}
	list->length--;
}

void print_list(LinkedList *list)
{
	Node *current;

	current = list->head;

	while(current != NULL)
	{
		printf("Nome: %s, RG: %i \n", current->data.name, current->data.rg);
		current = current->next;
	}
}

int main()
{
	LinkedList list;

	UserData joao;
	joao.name = "joao pedro";
	joao.rg = 22;

	UserData vitor;
	vitor.name = "victor emanuel";
	vitor.rg = 23;

	UserData maria;
	maria.name = "Maria clara";
	maria.rg = 21;

	list.length = 0;
	list.head = NULL;
	list.tail = NULL;

	insert_node(&list, joao, 0);
	insert_node(&list, vitor, 0);
	insert_node(&list, maria, -1);
	// delete_node(&list, 0);

	// printf("head: %s\ntail: %s\n", list.head->data.name, list.tail->data.name);

	print_list(&list);
}