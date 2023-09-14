#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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

void insert_node(LinkedList *list, UserData data, size_t pos)
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
	else if(pos == 0)
	{
		newNode->prev = NULL;
		newNode->data = data;
		newNode->next = list->head;
		list->head->prev = newNode;
		list->head = newNode;
	}
	else if(pos == -1)
	{
		list->tail->next = newNode;
		newNode->prev = list->tail;
		newNode->data = data;
		newNode->next = NULL;
		list->tail = newNode;
	}
	else
	{
		int count = 0;
		Node *current  = list->head;
		if(pos > list->length && pos < -1)
		{
			printf("posicao invalida\n");
			exit(1);
		}
		bool flag = flag < list->length/2 ? true : false;
		if(!flag)
		{
			current = list->tail;
			pos = list->length - pos;
		}
		pos = pos - 1;
		while(count <= pos)
		{
			if(count == pos)
			{
				newNode->prev = current;
				newNode->data = data;
				newNode->next = current->next;
				current->next = newNode;
			}
			current = current->next;
			count++;
		}
	}
	list->length++;
}

void delete_node(LinkedList *list, int pos)
{
	if(pos == 0 || pos == 1)
		list->head = list->head->next;
	else if(pos == -1)
	{
		list->tail = list->tail->prev;
		list->tail->next = NULL;
	}
	else
	{
		int count = 0;
		Node *current = list->head;
		if(pos > list->length && pos < -1)
		{
			printf("posicao invalida\n");
			exit(1);
		}
		bool flag = flag < list->length/2 ? true : false;
		if(!flag)
		{
			current = list->tail;
			pos = list->length - pos;
		}
		pos = pos - 1;
		while(count <= pos)
		{
			if(count == pos)
			{
				current->next->prev = current->prev;
				current->prev->next = current->next;
			}
			current = current->next;
			count++;
		}
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

int	ft_atoi(const char *nptr)
{
	int	i = 0;
	int	num = 0;

	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32))
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		num = (num * 10) + (nptr[i] - 48);
		i++;
	}
	return (num);
}

size_t	ft_strlen(const char *s)
{
	size_t	i = 0;

	while (s[i] != '\0')
		i++;
	return (i);
}

void readFile(LinkedList *list, char *file)
{
	FILE *fp;
	fp = fopen(file, "r");
	if(fp == NULL)
	{
		printf("erro ao abrir o arquivo\n");
		exit(1);
	}
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	while((read = getline(&line, &len, fp)) != EOF)
	{

		if(ft_strlen(line) < 9)
			continue;
		UserData newUser;
		char *rg = (char *)malloc(sizeof(char) * 9);
		char *name = (char *)malloc(sizeof(char) * (ft_strlen(line) - 8));

		int i = 0, j = 0, flag = 0;
		while (line[i] != '\0')
		{
			if(line[i] == ',')
			{
				flag = 1;
				j = 0;
			} else
			{
				if(flag)
					rg[j++] = line[i];
				else
					name[j++] = line[i];
			}
			i++;
		}

		name[j] = '\0';
		newUser.name = name;
		newUser.rg = ft_atoi(rg);
		insert_node(list, newUser, -1);
	}
	fclose(fp);
}


void create_file(char *name, LinkedList *list)
{
	FILE *fp;

	name = name == NULL ? "result.txt" : name;
	fp = fopen(name, "w");
	if(fp == NULL)
	{
		printf("erro ao criar o arquivo\n");
		exit(1);
	}
	Node *current = list->head;
	while(current != NULL)
	{
		fprintf(fp, "%s,%i\n", current->data.name, current->data.rg);
		current = current->next;
	}
	fclose(fp);
}

int main()
{


	LinkedList list;
	list.length = 0;
	list.head = NULL;
	list.tail = NULL;

	clock_t t;
    t = clock();
	readFile(&list, "./db/NomeRG10.txt");
    t = clock() - t;
	double cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

    printf("readFile() took %f seconds to execute \n", cpu_time_used);

	create_file("result.txt", &list);
	insert_node(&list, (UserData){"teste", 123456789}, 0);
	printf("tamanho da lista: %zu\n", list.length);
	printf("head: %s, %i\n", list.head->data.name, list.head->data.rg);
	printf("tail: %s, %i\n", list.tail->data.name, list.tail->data.rg);
	// print_list(&list);

	return 0;
}
