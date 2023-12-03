#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define clear() printf("\033[H\033[J")

void flush_in()
{
   int ch;
   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

typedef struct
{
	int comp;
	int mov;
} Cost;

typedef struct
{
	char *name;
	int rg;
} UserData;

typedef struct
{
	UserData data;
	int pos;
} Search_component;

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

Cost insert_node_linkedList(LinkedList *list, UserData data, size_t pos)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	Cost cost = {0, 0};


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
		cost.comp++;
	}
	else if(pos == -1)
	{
		list->tail->next = newNode;
		newNode->prev = list->tail;
		newNode->data = data;
		newNode->next = NULL;
		list->tail = newNode;
		cost.comp++;
	}
	else
	{
		int count = 1;
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
				cost.mov += 2;
			}
			cost.comp++;
			current = current->next;

			count++;
		}
	}
	list->length++;
	return cost;
}


void print_Linkedlist(LinkedList *list)
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

void read_file_to_linkedList(LinkedList *list, char *file)
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
	Cost cost = {0, 0};
	while((read = getline(&line, &len, fp)) != EOF)
	{
		if(ft_strlen(line) < 8)
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
		cost = insert_node_linkedList(list, newUser, -1);
	}
	fclose(fp);
}


int main()
{
    
}