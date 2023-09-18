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

void insert_node_linkedList(LinkedList *list, UserData data, size_t pos)
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

void insert_data_on_list(UserData **list, UserData data, int pos)
{
	int i = 2, lenght = (*list)[0].rg;

	if((*list)[1].name == NULL)
	{
		(*list) = (UserData *)malloc(sizeof(UserData) * 2);
		(*list)[0] = (UserData){data.name, data.rg};
		(*list)[1] = (UserData){NULL, 0};
		return;
	}

	if(pos > lenght)
	{
		printf("posicao invalida\n");
		return;
	}

	*list = (UserData *)realloc(*list, sizeof(UserData) * (lenght + 2));
	if(pos == 0)
	{
		while(i <= lenght)
		{
			(*list)[i + 1] = (UserData){(*list)[i].name, (*list)[i].rg};
			i++;
		}
		(*list)[0] = (UserData){data.name, data.rg};
	}

	else if(pos == -1)
	{
		(*list)[lenght] = (UserData){data.name, data.rg};
		(*list)[lenght + 1] = (UserData){NULL, 0};
		(*list)[0] = (UserData){"lenght", lenght + 1};
		return;
	}

	else
	{
		while((*list)[i].name != NULL)
		{
			if(i == pos)
			{
				int j = lenght;
				while(j >= i)
				{
					(*list)[j + 1] = (UserData){(*list)[j].name, (*list)[j].rg};
					j--;
				}
				(*list)[i] = (UserData){data.name, data.rg};
				break;
			}
			i++;
		}
	}
	(*list)[lenght + 1] = (UserData){NULL, 0};
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
		insert_node_linkedList(list, newUser, -1);
	}
	fclose(fp);
}


void read_file_to_list(UserData **list, char *file)
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
		newUser = (UserData){name, ft_atoi(rg)};
		insert_data_on_list(list, newUser, -1);
	}
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

int menu()
{
	int option = 0;
	printf("\nTRABALHO 01\n");
	printf("----- DIGITE O NUMERO DA OPÇÂO DESEJADA -----\n");
	printf("{00} - Para encerrar o programa \n");
	printf("{01} - Buscar um NOME a partir de um RG: \n");
	printf("{02} - Inserir uma amostra: \n");
	printf("{03} - Remover uma amostra: \n");
	printf("{04} - Imprimir lista  \n");
	printf("Digite uma opcao: ");
	int c;
	while((c = getchar()) != '\n' && c != EOF);
	return option;
}


UserData search_rg_linkedList(LinkedList *list, int rg)
{
	Node *current = list->head;
	while(current != NULL)
	{
		if(current->data.rg == rg)
			return current->data;
		current = current->next;
	}
	return (UserData){NULL, 0};
}

UserData serach_rg_list(UserData **list, int rg)
{
	int i = 0;
	while((*list)[i].name != NULL)
	{
		if((*list)[i].rg == rg)
			return (*list)[i];
		i++;
	}
	return (UserData){NULL, 0};
}

void print_list(UserData *list)
{
	int i = 0;
	while(list[i].name != NULL)
	{
		printf("Nome: %s, RG: %i \n", list[i].name, list[i].rg);
		i++;
	}
}

int main()
{
	LinkedList list;
	list.length = 0;
	list.head = NULL;
	list.tail = NULL;
	UserData *data;
	data = (UserData *)malloc(sizeof(UserData) * 2);
	data[0] = (UserData){"lenght", 0};
	data[1] = (UserData){NULL, 0};

	char *file = "./db/NomeRG10.txt";

	clock_t t;
	t = clock();
	read_file_to_linkedList(&list, file);
	t = clock() - t;
	double cpu_time_used = ((double)t)/CLOCKS_PER_SEC;
	printf("read_file_to_linkedList() levou %f segundos para ser executado \n", cpu_time_used);

	t = clock();
	read_file_to_list(&data, file);
	t = clock() - t;
	cpu_time_used = ((double)t)/CLOCKS_PER_SEC;
	printf("read_file_to_list() levou %f segundos para ser executado \n", cpu_time_used);

	create_file("result.txt", &list);
	insert_node_linkedList(&list, (UserData){"teste", 123456789}, 0);
	printf("tamanho da lista: %zu\n", list.length);
	printf("head: %s, %i\n", list.head->data.name, list.head->data.rg);
	printf("tail: %s, %i\n", list.tail->data.name, list.tail->data.rg);
	int rg;
	switch (menu())
	{

	case 0:
		printf("Encerrando o programa...\n");
		break;
	case 1:
		printf("Digite o RG: ");
		scanf("%i", &rg);
		printf("Buscando um NOME a partir de um RG: \n");

		t = clock();
		UserData user = search_rg_linkedList(&list, rg);
		t = clock() - t;
		cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

		printf("search_rg_linkedList() levou %f segundos para ser executado \n", cpu_time_used);
		t = clock();
		UserData user2 = serach_rg_list(&data, rg);
		t = clock() - t;
		cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

		printf("serach_rg_list() levou %f segundos para ser executado \n", cpu_time_used);
		printf("Nome: %s, RG: %i \n", user.name, user.rg);
		printf("Nome: %s, RG: %i \n", user2.name, user2.rg);
		menu();
	case 2:
		printf("Inserindo uma amostra: \n");
		printf("Digite o nome: ");
		char *name = (char *)malloc(sizeof(char) * 100);
		scanf("%s", name);
		printf("Digite o RG: ");
		scanf("%i", &rg);

		t = clock();
		insert_node_linkedList(&list, (UserData){name, rg}, -1);
		t = clock() - t;
		cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

		printf("insert_node_linkedList() levou %f segundos para ser executado \n", cpu_time_used);

		t = clock();
		insert_data_on_list(&data, (UserData){name, rg}, -1);
		t = clock() - t;
		cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

		printf("insert_data_on_list() levou %f segundos para ser executado \n", cpu_time_used);
		menu();
	case 4:
		printf("Imprimindo lista: \n");

		t = clock();
		print_Linkedlist(&list);
		t = clock() - t;
		cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

		printf("print_Linkedlist() levou %f segundos para ser executado \n", cpu_time_used);
		menu();
	default:
		break;
	}
	return 0;
}
