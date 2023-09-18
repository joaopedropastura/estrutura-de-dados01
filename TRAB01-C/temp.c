#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct
{
    char *name;
    int rg;
} UserData;

int	ft_atoi(const char *nptr)
{
	int	i = 0;
	int	num = 0;

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

void print_list(UserData *list)
{
	int i = 0;
	while(list[i].name != NULL)
	{
		printf("Nome: %s, RG: %i \n", list[i].name, list[i].rg);
		i++;
	}
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
		if(rg == NULL)
		{
			printf("erro ao alocar memoria\n");
			exit(1);
		}
		char *name = (char *)malloc(sizeof(char) * (read - 9));
		if(name == NULL)
		{
			printf("erro ao alocar memoria\n");
			exit(1);
		}
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
		// newUser = (UserData){name, ft_atoi(rg)};
		insert_data_on_list(list, (UserData){name, ft_atoi(rg)}, -1);
	}
}
int main()
{
	UserData *list;
	list = (UserData *)malloc(sizeof(UserData) * 2);
	list[0] = (UserData){"lenght", 0};
	list[1] = (UserData){NULL, 0};
	char *file = "./db/NomeRG100M.txt";


	clock_t t;
	t = clock();
	read_file_to_list(&list, file);
	t = clock() - t;
	double cpu_time_used = ((double)t)/CLOCKS_PER_SEC;
	printf("insert_data_on_list() levou %f segundos para ser executado \n", cpu_time_used);

	// insert_data_on_list(&list, (UserData){"Joao111", 111}, 5);
	// insert_data_on_list(&list, (UserData){"Joao222", 222}, -1);
	// insert_data_on_list(&list, (UserData){"Joao333", 333}, 1);
	// insert_data_on_list(&list, (UserData){"Joao444", 444}, 1);

	// print_list(list);
}


