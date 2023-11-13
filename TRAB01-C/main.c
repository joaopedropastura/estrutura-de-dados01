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

Cost remove_data_on_list(UserData **list, int pos)
{
	int i = 1, lenght = (*list)[0].rg;
	Cost cost = {0, 0};

	if((*list)[1].name == NULL)
	{
		printf("lista vazia\n");
		return cost;
	}

	if(pos > lenght)
	{
		printf("posicao invalida\n");
		return cost;
	}

	if(pos == 0)
	{
		while(i <= lenght)
		{
			(*list)[i] = (UserData){(*list)[i + 1].name, (*list)[i + 1].rg};
			i++;
			cost.mov++;
		}
		(*list)[0] = (UserData){"lenght", lenght - 1};
		cost.comp++;
		return cost;

	}

	else if(pos == -1)
	{
		(*list)[lenght] = (UserData){NULL, 0};
		(*list)[0] = (UserData){"lenght", lenght - 1};
		cost.comp++;
		cost.mov++;
		return cost;
	}

	else
	{
		while((*list)[i].name != NULL)
		{
			if(i == pos)
			{
				int j = i;
				while(j <= lenght)
				{
					(*list)[j] = (UserData){(*list)[j + 1].name, (*list)[j + 1].rg};
					j++;
					cost.mov++;
				}
				(*list)[0] = (UserData){"lenght", lenght - 1};
				break;
			}
			cost.comp++;
			i++;
		}
		return cost;
	}
	return cost;
}

Cost insert_data_on_list(UserData **list, UserData data, int pos)
{
	int i = 2, lenght = (*list)[0].rg;

	Cost cost = {0, 0};

	if((*list)[1].name == NULL)
	{
		(*list) = (UserData *)malloc(sizeof(UserData) * 3);
		(*list)[0] = (UserData){"lenght", 1};
		(*list)[1] = (UserData){data.name, data.rg};
		(*list)[2] = (UserData){NULL, 0};
		return cost;
	}

	if(pos > lenght)
	{
		printf("posicao invalida\n");
		return cost;
	}

	*list = (UserData *)realloc(*list, sizeof(UserData) * (lenght + 3));
	if(pos == 0)
	{
		int j = lenght;
		while(j >= 0)
		{
			(*list)[j + 1] = (UserData){(*list)[j].name, (*list)[j].rg};
			j--;
			cost.mov++;
		}
		(*list)[0] = (UserData){"lenght", lenght + 1};
		(*list)[1] = (UserData){data.name, data.rg};
		cost.comp++;
		return cost;
	}

	else if(pos == -1)
	{
		(*list)[lenght + 1] = (UserData){data.name, data.rg};
		(*list)[lenght + 2] = (UserData){NULL, 0};
		(*list)[0] = (UserData){"lenght", lenght + 1};
		cost.comp++;
		return cost;
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
					cost.mov++;
				}
				(*list)[i] = (UserData){data.name, data.rg};
				(*list)[lenght + 2] = (UserData){NULL, 0};
				(*list)[0] = (UserData){"lenght", lenght + 1};
				break;
			}
			cost.comp++;
			i++;
		}
		return cost;
	}

	return cost;
}

Cost delete_node(LinkedList *list, int pos)
{
	Cost cost = {0, 0};

	if(pos == 0 || pos == 1)
	{
		list->head = list->head->next;
		cost.mov++;
		cost.comp++;

		return cost;
	}
	else if(pos == -1)
	{
		list->tail = list->tail->prev;
		list->tail->next = NULL;
		cost.mov++;
		cost.comp++;
		return cost;
	}
	else
	{
		int count = 1;
		Node *current  = list->head;

		while(count <= pos)
		{
			if(count == pos)
			{
				current->next->prev = current->prev;
				current->prev->next = current->next;
				cost.mov = cost.mov + 2;
			}
			current = current->next;
			cost.comp++;
			count++;
		}
		return cost;
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
	Cost cost = {0, 0};

	while((read = getline(&line, &len, fp)) != EOF)
	{

		if(ft_strlen(line) < 8)
			continue;
		UserData newUser;
		char *rg = (char *)malloc(sizeof(char) * 10);
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
		cost = insert_data_on_list(list, newUser, -1);
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
	printf("{04} - Imprimir lista linkada\n");
	printf("{05} - Imprimir lista sequencial\n");
	printf("Digite uma opcao: ");
	scanf("%i", &option);
	flush_in();
	return option;
}

Search_component search_rg_linkedList(LinkedList *list, int rg)
{
	Node *current = list->head;
	int pos = 1;
	while(current != NULL)
	{
		if(current->data.rg == rg)
			return (Search_component){current->data, pos};
		current = current->next;
		pos++;
	}
	return (Search_component){NULL, 0};
}

Search_component serach_rg_list(UserData **list, int rg)
{
	int i = 1;
	while((*list)[i].name != NULL)
	{
		if((*list)[i].rg == rg)
			return (Search_component){(*list)[i], i};
		i++;
	}
	return (Search_component){NULL, 0};
}

void print_list(UserData *list)
{
	int i = 1;
	while(list[i].name != NULL)
	{
		printf("Nome: %s, RG: %i \n", list[i].name, list[i].rg);
		i++;
	}
}


int main()
{
	clear();
	LinkedList list;
	list.length = 0;
	list.head = NULL;
	list.tail = NULL;
	UserData *data;
	data = (UserData *)malloc(sizeof(UserData) * 2);
	data[0] = (UserData){"lenght", 0};
	data[1] = (UserData){NULL, 0};

	Cost cost_list = {0, 0};
	Cost cost_linkedlist = {0, 0};

	char *file = "../../db/NomeRG100M.txt";

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

	int rg, c;
	while (true)
	{
		switch (menu())
		{
			case 0:
				printf("Encerrando o programa...\n");
				break;

			case 1:
				clear();
				printf("Digite o RG: ");
				scanf("%i[^\n]", &rg);
				flush_in();
				printf("Buscando um NOME a partir de um RG: \n");

				t = clock();
				Search_component user = search_rg_linkedList(&list, rg);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

				printf("search_rg_linkedList() levou %f segundos para ser executado;\n	Nome: %s, RG: %i, pos: %i \n", cpu_time_used, user.data.name, user.data.rg, user.pos);
				t = clock();
				Search_component user2 = serach_rg_list(&data, rg);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

				printf("serach_rg_list() levou %f segundos para ser executado;\n	Nome: %s, RG: %i; pos: %i\n", cpu_time_used, user2.data.name, user2.data.rg, user2.pos);
				break;

			case 2:
				printf("Inserindo uma amostra: \n");
				printf("Digite o nome: ");
				char *name = (char *)malloc(sizeof(char) * 100);
				scanf("%s", name);
				flush_in();

				printf("Digite o RG: ");
				scanf("%i", &rg);
				flush_in();

				printf("Digite a posição na lista: ");
				scanf("%i", &c);
				flush_in();

				t = clock();
				cost_linkedlist = insert_node_linkedList(&list, (UserData){name, rg}, c);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

				printf("insert_node_linkedList() levou %f segundos para ser executado \n	C: %i M: %i \n", cpu_time_used, cost_linkedlist.comp, cost_linkedlist.mov);

				t = clock();

				cost_list = insert_data_on_list(&data, (UserData){name, rg}, c);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

				printf("insert_data_on_list() levou %f segundos para ser executado \n	C: %i M: %i\n", cpu_time_used, cost_list.comp, cost_list.mov);
				break;
			case 3:


				printf("Removendo uma amostra: \n");
				printf("Digite a posição na lista: ");
				scanf("%i", &rg);
				flush_in();
				
				t = clock();
				cost_linkedlist = delete_node(&list, rg);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

				printf("delete_node() levou %f segundos para ser executado \n	C: %i M: %i\n", cpu_time_used, cost_linkedlist.comp, cost_linkedlist.mov);
				printf("%i, %i\n", cost_linkedlist.mov, cost_linkedlist.comp);

				t = clock();
				cost_list = remove_data_on_list(&data, rg);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

				printf("remove_data_on_list() levou %f segundos para ser executado \n	C: %i M: %i\n", cpu_time_used, cost_list.comp, cost_list.mov);

				break;

			case 4:
				printf("Imprimindo lista: \n");

				t = clock();
				print_Linkedlist(&list);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

				printf("print_Linkedlist() levou %f segundos para ser executado \n", cpu_time_used);
				break;

			case 5:
				printf("Imprimindo lista: \n");

				t = clock();
				print_list(data);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

				printf("print_list() levou %f segundos para ser executado \n", cpu_time_used);
				break;

			default:
				break;
		}
	}
	return 0;
}
