#include "lib.h"

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
	printf("{06} - Ordenar utilizando o algoritmo Selection_sort()\n");
	printf("{07} - Ordenar utilizando o algoritmo Insertion_sort()\n");
	printf("{08} - Ordenar utilizando o algoritmo Bubble_sort()\n");
	printf("Digite uma opcao: ");
	scanf("%i", &option);
	flush_in();
    
	return option;
}