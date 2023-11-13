#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define clear() printf("\033[H\033[J")

typedef struct
{
	unsigned long int comp;
	unsigned long int mov;
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

void flush_in()
{
   int ch;
   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}


// Cost bubble_sort(UserData **list)
// {
//     int i = 1, j = 1, lenght = (*list)[0].rg;
//     Cost cost = {0, 0};

//     while(i <= lenght)
//     {
//         j = 1;
//         while(j <= lenght - i)
//         {
//             if((*list)[j].rg > (*list)[j + 1].rg)
//             {
//                 UserData aux = (*list)[j];
//                 (*list)[j] = (*list)[j + 1];
//                 (*list)[j + 1] = aux;
//                 cost.mov++;
//             }
//             j++;
//             cost.comp++;
//         }
//         i++;
//     }
//     return cost;
// }

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
	printf("{05} - Imprimir lista sequencial\n");
	printf("{06} - Ordenar utilizando o algoritmo Selection_sort()\n");
	printf("{07} - Ordenar utilizando o algoritmo Insertion_sort()\n");
	printf("{08} - Ordenar utilizando o algoritmo Bubble_sort()\n");
	printf("{09} - Ordenar utilizando o algoritmo Quick_sort()\n");
	printf("{10} - Ordenar utilizando o algoritmo merge_sort()\n");
	printf("{11} - Ordenar utilizando o algoritmo shell_sort()\n");
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
	Cost cost = {0, 0};
	int i = 1;
	while((*list)[i].name != NULL)
	{
		if((*list)[i].rg == rg)
			return (Search_component){(*list)[i], i};
		cost.comp++;
		i++;
	}
	printf("\nC: %lu M: %lu \n", cost.comp, cost.mov);
	return (Search_component){NULL, 0};
}


Cost insertion_sort(UserData **list)
{
    int i = 2, j = 1, lenght = (*list)[0].rg;
    Cost cost = {0, 0};

    while(i <= lenght)
    {
        UserData aux = (*list)[i];
        j = i - 1;
        while(j >= 1 && (*list)[j].rg > aux.rg)
        {
            (*list)[j + 1] = (*list)[j];
            j--;
            cost.comp++;
            cost.mov++;
        }
        (*list)[j + 1] = aux;
        i++;
        cost.mov++;
    }
    return cost;
}

Cost selection_sort(UserData **list)
{
    int i = 1, j = 1, min = 0, lenght = (*list)[0].rg;
    Cost cost = {0, 0};

    while(i <= lenght)
    {
        j = i + 1;
        min = i;
        while(j <= lenght)
        {
            if((*list)[j].rg < (*list)[min].rg)
                min = j;
            j++;
            cost.comp++;
        }
        UserData aux = (*list)[i];
        (*list)[i] = (*list)[min];
        (*list)[min] = aux;
        i++;
        cost.mov++;
    }
    return cost;
}

Cost bubble_sort(UserData **list)
{
    int i = 1, j = 1, lenght = (*list)[0].rg;
    Cost cost = {0, 0};

    while(i <= lenght)
    {
        j = 1;
        while(j <= lenght - i)
        {
            if((*list)[j].rg > (*list)[j + 1].rg)
            {
                UserData aux = (*list)[j];
                (*list)[j] = (*list)[j + 1];
                (*list)[j + 1] = aux;
                cost.mov+=2;
            }
            j++;
            cost.comp++;
        }
        i++;
    }
    return cost;
}


Cost shell_sort(UserData *data)
{
	int lenght = data[0].rg;
	Cost cost = {0, 0};
	int gap = 1;
	while(gap < lenght)
		gap = 3 * gap + 1;
	while(gap > 1)
	{
		gap /= 3;
		for(int i = gap + 1; i <= lenght; i++)
		{
			UserData aux = data[i];
			int j = i - gap;
			while(j >= 1 && aux.rg < data[j].rg)
			{
				data[j + gap] = data[j];
				j -= gap;
				cost.mov++;
				cost.comp++;
			}
			data[j + gap] = aux;
			cost.mov++;
		}
	}
	return cost;
}


Cost merge_sort(UserData **data)
{
	int lenght = (*data)[0].rg;
	Cost cost = {0, 0};

	if(lenght == 1)
		return cost;
	
	int mid = lenght / 2;
	UserData *left = (UserData *)malloc(sizeof(UserData) * (mid + 1));
	UserData *right = (UserData *)malloc(sizeof(UserData) * (lenght - mid + 1));
	if(left == NULL || right == NULL)
	{
		printf("erro ao alocar memoria\n");
		exit(1);
	}
	int i = 1;
	while(i <= mid)
	{
		left[i] = (UserData){(*data)[i].name, (*data)[i].rg};
		i++;
		cost.mov++;
	}
	left[0] = (UserData){"lenght", mid};

	i = mid + 1;
	while(i <= lenght)
	{
		right[i - mid] = (UserData){(*data)[i].name, (*data)[i].rg};
		i++;
		cost.mov++;
	}
	right[0] = (UserData){"lenght", lenght - mid};

	merge_sort(&left);
	merge_sort(&right);

	int j = 1, k = 1, l = 1;
	while(j <= left[0].rg && k <= right[0].rg)
	{
		if(left[j].rg < right[k].rg)
		{
			(*data)[l] = (UserData){left[j].name, left[j].rg};
			j++;
			cost.mov++;
		}
		else
		{
			(*data)[l] = (UserData){right[k].name, right[k].rg};
			k++;
			cost.mov++;
		}
		l++;
		cost.comp++;
	}

	while(j <= left[0].rg)
	{
		(*data)[l] = (UserData){left[j].name, left[j].rg};
		j++;
		l++;
		cost.mov++;
	}

	while(k <= right[0].rg)
	{
		(*data)[l] = (UserData){right[k].name, right[k].rg};
		k++;
		l++;
		cost.mov++;
	}
	return cost;
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


Cost quick_sort(UserData *data, int began, int end)
{
	int i, j, pivo, aux;
	i = began;
	j = end-1;
    Cost cost = {0, 0};
	UserData db;
	pivo = data[(began + end) / 2].rg;
	while(i <= j)
	{
		while(data[i].rg < pivo && i < end)
			i++;
		while(data[j].rg > pivo && j > began)
			j--;
		if(i <= j)
		{
			db = data[i];
			aux = data[i].rg;
			data[i].rg = data[j].rg;
			data[j].rg = aux;
			i++;
			j--;
			cost.mov++;
			cost.comp++;
		}
		cost.comp++;


	}
	if(j > began)
		quick_sort(data, began, j+1);
	if(i < end)
		quick_sort(data, i, end);
	return cost;
}


Search_component binary_search(UserData *data, int rg)
{
	int lenght = data[0].rg;
	int began = 1, end = lenght;
	Cost cost = {0, 0};
	while(began <= end)
	{
		int mid = began + (end - began) / 2;
		if(data[mid].rg == rg)
		{
			printf("\n%i, %s\n", data[mid].rg, data[mid].name);
			printf("C: %lu M: %lu \n", cost.comp, cost.mov);
			return (Search_component){data[mid], mid};
		}
		else if(data[mid].rg < rg)
			began = mid + 1;
		else
			end = mid - 1;
		cost.comp++;
	}

	return (Search_component){NULL, 0};
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

	char *file = "../../db/NomeRG10.txt";
	Search_component user;
	clock_t t;
	double cpu_time_used = ((double)t)/CLOCKS_PER_SEC;


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
				Search_component user2 = serach_rg_list(&data, rg);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

				printf("serach_rg_list() levou %f segundos para ser executado;\n	Nome: %s, RG: %i; pos: %i\n", cpu_time_used, user2.data.name, user2.data.rg, user2.pos);

				t = clock();
				user = binary_search(data, rg);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;
				printf("binary_search() levou %f segundos para ser executado \n	Nome: %s Posição: %i\n", cpu_time_used, user.data.name, user.pos);
				
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

				cost_list = insert_data_on_list(&data, (UserData){name, rg}, c);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

				printf("insert_data_on_list() levou %f segundos para ser executado \n	C: %lu M: %lu\n", cpu_time_used, cost_list.comp, cost_list.mov);
				break;
			case 3:


				printf("Removendo uma amostra: \n");
				printf("Digite a posição na lista: ");
				scanf("%i", &rg);
				flush_in();
	
				t = clock();
				cost_list = remove_data_on_list(&data, rg);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

				printf("remove_data_on_list() levou %f segundos para ser executado \n	C: %lu M: %lu\n", cpu_time_used, cost_list.comp, cost_list.mov);

				break;

			case 5:
				printf("Imprimindo lista: \n");

				t = clock();
				print_list(data);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

				printf("print_list() levou %f segundos para ser executado \n", cpu_time_used);
				break;

			
            case 6:
                printf("Ordenando lista: \n");
                t = clock();
                cost_list = selection_sort(&data);
                t = clock() - t;
                cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

                printf("selection_sort() levou %f segundos para ser executado \n	C: %lu M: %lu\n", cpu_time_used, cost_list.comp, cost_list.mov);
                break;
            
			case 7:
				printf("Ordenando lista: \n");
				t = clock();
				cost_list = insertion_sort(&data);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

				printf("insertion_sort() levou %f segundos para ser executado \n	C: %lu M: %lu\n", cpu_time_used, cost_list.comp, cost_list.mov);
				break;

			case 8:
				printf("Ordenando lista: \n");
				t = clock();
				cost_list = bubble_sort(&data);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;

				printf("insertion_sort() levou %f segundos para ser executado \n	C: %lu M: %lu\n", cpu_time_used, cost_list.comp, cost_list.mov);
				break;

			case 9:
				printf("Ordenando lista: \n");
				t = clock();
				cost_list = quick_sort(data, 1, data[0].rg + 1);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;
				printf("quick_sort() levou %f segundos para ser executado \n	C: %lu M: %lu\n", cpu_time_used, cost_list.comp, cost_list.mov);
				break;

			case 10:
				printf("Ordenando lista: \n");
				t = clock();
				cost_list = merge_sort(&data);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;
				printf("insertion_sort() levou %f segundos para ser executado \n	C: %lu M: %lu\n", cpu_time_used, cost_list.comp, cost_list.mov);

			case 11:
				printf("Ordenando lista: \n");
				t = clock();
				cost_list = shell_sort(data);
				t = clock() - t;
				cpu_time_used = ((double)t)/CLOCKS_PER_SEC;
				printf("insertion_sort() levou %f segundos para ser executado \n	C: %lu M: %lu\n", cpu_time_used, cost_list.comp, cost_list.mov);

            default:
				break;

		}
	}
	return 0;
}
