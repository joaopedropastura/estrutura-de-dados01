#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include <windows.h>
#define TAM 256 //pega a tabela ascii inteira + /0

//fazer um por um, organizado
//frequencia
//lista
//arvore
//dicionario
//codifica descodifica
//compacta e descompacta

typedef struct no{
    unsigned char caracter;
    int frequencia; //frequencia do caracter
    struct no *esquerda, *direita, *proximo;
}No;

typedef struct{
    No *inicio;
    int tam;
}Lista;

//TABELA FREQUENCIA

void inicializa_tabela_com_zero(unsigned int tabela[]){
    int i;
    for(i = 0; i < TAM; i++)
        tabela[i] = 0;
}

void preenche_tabela_frequencia(unsigned char texto[], unsigned int tab[]){
    int i = 0;
    while(texto[i] != '\0'){
        tab[texto[i]]++;
        i++;
    }
}

void imprime_tabela_frequencia(unsigned int tab[]){
    printf("TABELA DE FREQUENCIA\n");
    for(int i = 0; i < TAM; i++){
        if(tab[i] > 0)
            printf("%d = %u = %c\n", i, tab[i], i);
    }
}

//LISTA

void criar_lista(Lista *lista){
    lista->inicio = NULL;
    lista->tam = 0;
}

void inserir_ordenado(Lista *lista, No *no){
    No *aux;

    //lista vazia
    if(lista->inicio == NULL){
        lista->inicio = no;
    }
    // tem frequencia menor q o inicio, primeiro no da lista
    else if(no->frequencia < lista->inicio->frequencia){
        no->proximo = lista->inicio;
        lista->inicio = no;
    }
    //inserção no meio ou final
    else{
        aux = lista->inicio;
        while(aux->proximo && aux->proximo->frequencia <= no->frequencia)
            aux = aux->proximo;
        no->proximo = aux->proximo;
        aux->proximo = no;
    }
    lista->tam++;
}

void preencher_lista(unsigned int tab[], Lista *lista){
    No * novo;
    for(int i = 0; i < TAM; i++){
        if(tab[i] > 0){
            novo = malloc(sizeof(No));
            if(novo){
                novo->caracter = i;
                novo->frequencia = tab[i];
                novo->direita = NULL;
                novo->esquerda = NULL;
                novo->proximo = NULL;

                inserir_ordenado(lista, novo);

            }else{
                printf("\tERRO AO ALOCAR MEMORIA AO PREENCHER LISTA\n");
                break;
            }
        }
    }
}

void imprime_lista(Lista *lista){
    No *aux = lista->inicio;

    printf("\nLISTA ORDENADA: TAMANHO %d\n", lista->tam);
    while(aux){
        printf("Caracter: %c Frequencia: %d\n", aux->caracter, aux->frequencia);
        aux = aux->proximo;
    }

}
// ARVORE DE HUFFMANN

No* remove_inicio(Lista* lista){
    No *aux = NULL;

    if(lista->inicio){
        aux = lista->inicio;
        lista->inicio = aux->proximo;
        aux->proximo = NULL;
        lista->tam--;
    }

    return aux;
}

No* monta_arvore(Lista *lista){
    No *first, *second, *novo;
    while(lista->tam > 1){
        first = remove_inicio(lista);
        second = remove_inicio(lista);
        novo = malloc(sizeof(No));

        if(novo){
            novo->caracter = '+';
            novo->frequencia = first->frequencia + second->frequencia;
            novo->esquerda = first;
            novo->direita = second;
            novo->proximo = NULL;

            inserir_ordenado(lista, novo);
        }else{
            printf("\n\tERRO AO ALOCAR MEMORIA AO MONTAR A ARVORE\n");
            break;
        }
    }
    return lista->inicio;
}

void imprime_arvore(No *root, int tam){
    if(root->esquerda == NULL && root->direita == NULL)
        printf("Folha: %c  Altura: %d\n", root->caracter, tam);
    else{
        imprime_arvore(root->esquerda, tam + 1);
        imprime_arvore(root->direita, tam + 1);
    }
}

// DICIONARIO (tabela de codigos)

int altura_da_arvore(No *root){
    int esquerda = 0, direita = 0;

    if(root == NULL) //chegou na folha
    {
        return -1;
    }
    else{
        esquerda = altura_da_arvore(root->esquerda) + 1;
        direita = altura_da_arvore(root->direita) + 1;

        if(esquerda > direita)
            return esquerda;
        else
            return direita;
    }

}
//colunas = altura + 1
char **aloca_dic(int colunas){
    char **dic;

    dic = malloc(sizeof(char*) * TAM);

    for(int i = 0; i <TAM; i++)
        dic[i] = calloc(colunas, sizeof(char)); //limpa a regiao da memoria

    return dic;
}

void gera_dic(char **dic, No *root, char *caminho, int colunas){
    char esquerda[colunas], direita[colunas];
    if(root->esquerda == NULL && root->direita == NULL)//folha
    {
        strcpy(dic[root->caracter], caminho);
    }
    else{
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        strcat(esquerda, "0");
        strcat(direita, "1");

        gera_dic(dic, root->esquerda, esquerda, colunas);
        gera_dic(dic, root->direita, direita, colunas);
    }
}

void imprime_dic(char **dic){
    printf("\nDICIONARIO\n");
    for( int i = 0; i< TAM; i++){
        if(strlen(dic[i]) > 0)
            printf("%3d: %s\n", i, dic[i]);
    }
}


// codificação

int tamanho_string(char **dic, unsigned char *texto){
    int i = 0, tam = 0;
    while(texto[i] != '\0'){
        tam = tam + strlen(dic[texto[i]]);
        i++;
    }
    return tam + 1;
}

char* codificar(char **dic, unsigned char* texto){
    int tam = tamanho_string(dic, texto);
    char *codigo = calloc(tam, sizeof(char));
    int i = 0;
    while(texto[i] != '\0'){
        strcat(codigo, dic[texto[i]]);
        i++;
    }

    return codigo;
}


// decodificação

char* decodificar(unsigned char texto[], No *root){
    int i = 0;
    No *aux = root;
    char temp[2];
    char *decodificado = calloc(strlen(texto), sizeof(char));

    while(texto[i] != '\0'){
        if(texto[i] == '0')
            aux = aux->esquerda;
        else
            aux = aux->direita;

        if(aux->direita == NULL && aux->esquerda == NULL)//folha
        {
            temp[0] = aux->caracter;
            temp[1] = '\0';
            strcat(decodificado, temp);
            aux = root;
        }
        i++;
    }
    return decodificado;
}

// compactação

void compactar(unsigned char texto[]){
    FILE *arquivo = fopen("compactado.moll", "wb");
    int i = 0, j = 7;
    unsigned char byte = 0, masc;

    if(arquivo){
        while(texto[i] != '\0'){
            masc = 1;
            if(texto[i] == '1'){ //altera
                masc = masc << j;
                byte = byte | masc; //salva os bits
            }
            j--;

            if(j < 0){//percorreu 8 bits = 1 byte
                fwrite(&byte, sizeof(unsigned char), 1, arquivo);
                j = 7;
                byte = 0;
                //reseta pros proximos bits
            }
            i++;
        }
        if(j != 7) //caso nao for multiplo de 8
            fwrite(&byte, sizeof(unsigned char), 1, arquivo);
        fclose(arquivo);
    }
    else{
        printf("\n\nErro ao abrir arquivo para compactar");
    }
}

// descompactar

unsigned int bit_um(unsigned char byte, int i){
    unsigned char masc = (1 << i); //1000000
    return byte & masc; //isso aq eh piragem de ter funcionado
}

void descompactar(No *root){
    FILE *arquivo = fopen("compactado.moll", "rb");
    unsigned char byte;
    int i;
    No *aux = root;

    if(arquivo){
        while(fread(&byte, sizeof(unsigned char),1,arquivo)){
            for(i = 7; i >= 0; i--){
                if(bit_um(byte, i))
                    aux = aux->direita;
                else
                    aux = aux->esquerda;

                if(aux->direita == NULL && aux->esquerda == NULL){
                    printf("%c", aux->caracter);
                    aux = root;
                }
            }
        }
        fclose(arquivo);
    }
    else{
        printf("\n\nErro ao abrir arquivo para descompactar");
    }
}

//manipulação e abertura de texto

int tam_arquivo(char* path){
    FILE *arquivo = fopen(path, "r");
    int tam = 0;

    if(arquivo){
        while(fgetc(arquivo) != -1)
            tam++;
        fclose(arquivo);
    }
    else
        printf("Erro ao abrir o arquivo mencionado");

    return tam;
}

void ler_arquivo(unsigned char *texto, char *path){
    FILE *arquivo = fopen(path, "r");
    char letra;
    int i = 0;

    if(arquivo){
        //end of file
        while(!feof(arquivo)){
            letra = fgetc(arquivo);
            if(letra != -1){
                texto[i] = letra;
                i++;
            }
        }
        fclose(arquivo);
    }
    else
        printf("Erro ao abrir o arquivo mencionado");
}

int main(){
    //char -128 a 127
    //unsigned char 0 a 255 para alcançar a tabela ASCII
    unsigned char *texto;
    unsigned int tabela_frequencia[TAM];
    Lista lista;
    No *arvore_huffman;
    int colunas, tam;
    char **dic;
    char *codificado, *decodificado;
    char arquivo[20];
    int opcao;

    //SetConsoleOutputCP(65001);
    while (1) {
        printf("\n===== MENU =====\n");
        printf("1. Ler e apresentar um arquivo de texto\n");
        printf("2. Inicializar e apresentar a tabela de frequência\n");
        printf("3. Inicializar e apresentar a lista encadeada ordenada\n");
        printf("4. Inicializar e apresentar a árvore de Huffman\n");
        printf("5. Inicializar e apresentar o dicionário\n");
        printf("6. Inicializar e apresentar a codificação do texto\n");
        printf("7. Inicializar e apresentar a decodificação do texto\n");
        printf("8. Compactar em um arquivo\n");
        printf("9. Descompactar um arquivo\n");
        printf("10. Procurar palavra no arquivo\n");
        printf("11. Sair\n");
        printf("Digite a opção desejada: ");
        scanf("%i", &opcao);
        getchar(); // Limpar o caractere de nova linha (\n)

        switch(opcao){
            case 1:
                printf("Escreva o nome do arquivo que deseja: ");
                scanf("%s", arquivo);
                printf("%s", arquivo);

                tam = tam_arquivo(arquivo);
                texto = calloc(tam + 2, sizeof(unsigned char));
                ler_arquivo(texto, arquivo);
                printf("\nTEXTO\n\n%s", texto);
                break;
            case 2:
                //TABELA DE FREQUENCIA
                inicializa_tabela_com_zero(tabela_frequencia);
                preenche_tabela_frequencia(texto, tabela_frequencia);
                imprime_tabela_frequencia(tabela_frequencia);
                break;
            case 3:
                //LISTA ORDENADA
                criar_lista(&lista);
                preencher_lista(tabela_frequencia, &lista);
                imprime_lista(&lista);
                break;
            case 4:
                //ARVORE
                arvore_huffman = monta_arvore(&lista);
                printf("\nArvore de Huffman\n");
                imprime_arvore(arvore_huffman, 0);
                break;
            case 5:
                //DICIONARIO
                colunas = altura_da_arvore(arvore_huffman) + 1;
                dic = aloca_dic(colunas);
                gera_dic(dic, arvore_huffman, "", colunas);
                imprime_dic(dic);
                break;
            case 6:
                //CODIFICAÇÃO
                codificado = codificar(dic, texto);
                printf("\nTexto codificado: %s\n", codificado);
                break;
            case 7:
                //DECODIFICAÇÃO
                decodificado = decodificar(codificado, arvore_huffman);
                printf("\nTexto decodificado: %s\n", decodificado);
                break;
            case 8:
                //COMPACTAÇÃO
                compactar(codificado);
                break;
            case 9:
                //DESCOMPACTAÇÃO
                descompactar(arvore_huffman);
                break;
            case 10:
                printf("Pesquisar sobre algoritmo de Boyer-Moore");
                break;
            case 11:
                exit(0);
                break;
        }
    }
    return 0;
}
