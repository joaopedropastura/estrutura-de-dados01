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

void insertNode(LinkedList *list, UserData data, int flag)
{
	Node *newNode = (Node *)malloc(sizeof(Node));

	if (!newNode)
	{
		printf("erro ao alocar memoria\n");
		exit(1);
	}
	if(list->length == 0)
	{
		list->head = newNode;
		list->tail = newNode;
		list->tail->next = NULL;
	}
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
	list->length++;
}

void deleteNode(LinkedList *list, int flag)
{
	if(flag == 0)
		list->head = list->head->next;
	if(flag == -1)
		list->tail = list->tail->prev;
		list->tail->next = NULL;
}

void printList(LinkedList *list)
{
	Node *current = (Node *)malloc(sizeof(Node));

	if (!current)
	{
		printf("erro ao alocar memoria\n");
		exit(1);
	}
	current = list->head;
	while(current != NULL)
	{
		printf("Nome: %s, RG: %i\n", current->data.name, current->data.rg);
		current = current->next;
	}
}

int main()
{
	LinkedList list;

	UserData data;
	data.name = "joao pedro";
	data.rg = 22;

	UserData data1;
	data1.name = "victor emanuel";
	data1.rg = 23;

	UserData data2;
	data2.name = "Maria clara";
	data2.rg = 21;

	list.length = 0;
	list.head = NULL;
	list.tail = NULL;

	insertNode(&list, data, 0);
	insertNode(&list, data1, 0);
	insertNode(&list, data2, 0);

	// deleteNode(&list, -1);

	printList(&list);
}