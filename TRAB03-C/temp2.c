#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PALAVRAS 1500
#define MAX_P_UNICA 25
#define MAX_POS_VET 30
#define MAX_HISTORIA 6000

int tam = 0;
int tam2 = 0;

typedef struct {
    char palavra[40];
    int ind;
    int ja_foi;
} Palavra;

typedef struct {
    char p_unica[MAX_P_UNICA];
    int pos_vet[MAX_POS_VET];
    int freq;
} Word;

void guardar_palavra(Palavra palavras[], int i, char word[], int ind) {
    word[i] = '\0';
    palavras[tam].ind = ind;
    strcpy(palavras[tam].palavra, word);
    tam++;
    //printf("%d\n\n", ind); // tirar apenas teste
}

void ler_arquivo(char historia[]) {
    FILE* file = fopen("./historia.txt", "r");
    int i = 0;
    char letra;

    if (file) {
        //while ((letra = fgetc(file)) != EOF && i < MAX_HISTORIA - 1) {
        while (!feof(file) && !ferror(file)){
            letra = fgetc(file);
            historia[i] = tolower(letra);
            if(letra == EOF){
               historia[i - 1] = '\0'; //tive q implementar esse if
               break;
                }
            i++;
        }
        //historia[i] = '\0';
        printf("\nArquivo lido com sucesso\n");
    }
    else {
        printf("Erro ao abrir o arquivo\n");
    }
    fclose(file);
}

void formar_palavras(char historia[], Palavra palavras[]){
    int j = 0, i;
    char word[40];
    int ind, char_apos_pt = 0;
    char letra;

    while(historia[j] != '\0'){
        i = 0;
        ind = j;
        if(!char_apos_pt)
            letra = historia[j];
        while((letra >= 65 && letra <= 90) || (letra >= 97 && letra <= 122) || ((letra == '-') && (historia[j + 1] >= 97 && historia[j + 1] <= 122))){ //vericando se é uma letra ou uma palavra com hifen
            word[i] = letra;
            j++;
            letra = historia[j];
            i++;
        }
        if(letra == ' '){  //verifica se apos a letra é um espaco e inserindo esse espaco junto com a palavra
            word[i] = ' ';
            i++;
            guardar_palavra(palavras, i, word, ind);
            char_apos_pt = 0;
            j++;
        }
        else{
            if(historia[j - 1] != ' ') //verificando se antes da pontuacao há um espaco
                guardar_palavra(palavras, i, word, ind);
            i = 0;
            while ((letra < 65 || letra > 90) && (letra < 97 || letra > 122)){ //enquanto nao for uma letra
                ind = j;
                word[i] = letra;
                j++;
                letra = historia[j];
                i++;
                if(letra =='\0'){ //verificando se nao é o fim da string historia
                    break;
                }
                if((letra != ' ') && ((letra < 65 || letra > 90) && (letra < 97 || letra > 122))){ //verificando se o prox char é diferente de espaco e nao é uma letra
                    guardar_palavra(palavras, i, word, ind);
                    i = 0;
                }else if((letra >= 65 && letra <= 90) || (letra >= 97 && letra <= 122)){    //caso apos o ' ' seja um char a flag char_apos_pt = 1 para n ir pra prox letra
                    char_apos_pt = 1;
                }
            }
            guardar_palavra(palavras, i, word, ind);
        }
    }
}

/*void palavras_unicas(Palavra palavras[], Word words_u[]) {
    int i, j, freq;
    int ja_foi;

    for (i = 0; i <= tam; i++) {
        if (isalpha(palavras[i].palavra[0])) {
            if (palavras[i].ja_foi) {
                continue;
            }

            freq = 1;
            palavras[i].ja_foi;

            for (j = i + 1; j < tam; j++) {
                if (strcasecmp(palavras[i].palavra, palavras[j].palavra) == 0) {
                    freq++;
                    palavras[j].ja_foi = 1;
                }
            }

            strcpy(words_u[tam2].p_unica, palavras[i].palavra);
            words_u[tam2].freq = freq;
            tam2++;
        }
    }
}*/

void palavras_unicas(Palavra palavras[], Word words_u[]) {
    int i, j, freq;
    int ja_foi;

    for (i = 0; i < tam; i++) {
        if (isalpha(palavras[i].palavra[0])) {
            if (palavras[i].ja_foi) {
                continue;
            }

            freq = 1; // Inicializa a frequência com 1 (já encontramos uma ocorrência)

            for (j = i + 1; j < tam; j++) {
                if (strcasecmp(palavras[i].palavra, palavras[j].palavra) == 0) {
                    freq++;
                    palavras[j].ja_foi = 1;
                }
            }

            // Verifica se a palavra já existe no vetor words_u
            int palavra_existente = 0;
            for (j = 0; j < tam2; j++) {
                if (strcasecmp(words_u[j].p_unica, palavras[i].palavra) == 0) {
                    // A palavra já existe, incrementa a frequência
                    words_u[j].freq += freq;
                    palavra_existente = 1;
                    break;
                }
            }

            // Se a palavra não existe no vetor words_u, adiciona como nova palavra única
            if (!palavra_existente) {
                strcpy(words_u[tam2].p_unica, palavras[i].palavra);
                words_u[tam2].freq = freq;
                tam2++;
            }
        }
    }
}


void frequencia_palavras(Word words_u[], Palavra palavras[]) {
    int i = 0, j, k;
    int res;
    while (i < tam2) {
        j = 0;
        k = 0;
        words_u[i].freq = 0;
        while (j <= tam) {
            res = strcasecmp(words_u[i].p_unica, palavras[j].palavra);
            if (res == 0 || res == 32 || res == -32) { //modificquei
                words_u[i].freq++;
                words_u[i].pos_vet[k] = palavras[j].ind;
                k++;
            }
            j++;
        }
        i++;
    }
}

void criar_arquivo_invertido(Word words_u[]) {
    FILE* arquivo = fopen("arquivo_invertido.txt", "w");
    int i;
    int k;

    if (arquivo) {
        for (i = 0; i < tam2; i++) {
            fprintf(arquivo, "palavra: %s | freq: %d | posicoes: ", words_u[i].p_unica, words_u[i].freq);
            k = 0;
            while (/*words_u[i].pos_vet[k] != '\0'*/ k < words_u[i].freq && k < MAX_POS_VET) {
                fprintf(arquivo, "%d / ", words_u[i].pos_vet[k]);
                k++;
            }
            fprintf(arquivo, "\n\n");
        }
        fclose(arquivo);
        printf("Arquivo invertido criado com sucesso\n");
    }
    else {
        printf("Erro ao abrir o arquivo para escrita\n");
    }
}

Word procurar_palavra(Word words_u[]) {
    int i = 0;
    Word palavra_procurada;
    int res;
    printf("Qual palavra esta procurando?\n");
    scanf(" %25[^\n]", palavra_procurada.p_unica);
    getchar();
    while (i < tam2) {
        res = strcasecmp(palavra_procurada.p_unica, words_u[i].p_unica);
        if (res == 0 || res == 32 || res == -32)
        {
            return words_u[i];
        }
        i++;
    }
    palavra_procurada.freq = 0;
    palavra_procurada.pos_vet[0] = -1;
    return palavra_procurada;
}

void ocorrencia_palavra(Word palavra) {
    if (palavra.freq == 0)
        printf("\nA palavra NAO aparece no texto\n");
    else
        printf("\nA palavra aparece %d vezes no texto!\n", palavra.freq);
}

void posicao_palavra_no_arquivo(Word palavra, int i) {
    if (palavra.pos_vet[0] == -0)
        printf("\nA palavra NAO aparece em nenhuma posicao, pois ela nao esta no texto\n");
    else
        printf("\nA palavra aparece na posicao %d\n", palavra.pos_vet[i]);
}

void pedaco_da_frase_com_a_palavra(Word palavra, int i, char historia[]) {
    int x;
    printf("Pedaco da frase com a palavra:\n");
    for (x = palavra.pos_vet[i] - 0; x <= palavra.pos_vet[i] + 30; x++) {
        printf("%c", historia[x]);
    }
    printf("\n");
}

void pedaco(char historia[],int i){
     int i2 = i - 30;
     int i3 = i + 30;

     for(i2; i2 <= i3; i2++){
             printf("%c", historia[i2]);
             }
     }

void menu_c(int* opcao_c) {
    printf("\n1 - O numero de ocorrencias da palavra\n2 - Sua posicao N no arquivo\n3 - Algumas palavras incluindo a propria palavra (pedacos da palavra procurada)\n0 - Voltar para o menu principal\n");
    scanf(" %d", opcao_c);
    getchar();
}

void menu_d(int* opcao_d) {
    printf("\n1 - Sua posicao N no arquivo\n2 - Algumas palavras incluindo a propria palavra (pedacos da palavra procurada)\n0 - Voltar para o menu principal\n");
    scanf(" %d", opcao_d);
    getchar();
}

void menu_opcoes() {
    printf("\na - Ler um arquivo texto\nb - Apresentar o arquivo invertido\nc - Procurar uma palavra\nd - Proxima ocorrencia\ne - Sair\n");
}

int main() {
    char historia[MAX_HISTORIA], opcao;
    int opcao_c, opcao_d, i = 1, j = 1;
    Palavra palavras[MAX_PALAVRAS];
    Word words_u[MAX_PALAVRAS];
    Word palavra_procurada;

    do {
        menu_opcoes();
        scanf(" %c", &opcao);
        getchar();

        switch (opcao) {
            case 'a':
                system("cls");
                tam = 0;
                tam2 = 0;
                ler_arquivo(historia);
                formar_palavras(historia, palavras);
                palavras_unicas(palavras, words_u);
                frequencia_palavras(words_u, palavras);
                break;
            case 'b':
                system("cls");
                criar_arquivo_invertido(words_u);
                break;
            case 'c':
                palavra_procurada = procurar_palavra(words_u);
                do {
                    menu_c(&opcao_c);
                    switch (opcao_c) {
                        case 1:
                            ocorrencia_palavra(palavra_procurada);
                            break;
                        case 2:
                            posicao_palavra_no_arquivo(palavra_procurada, 0);
                            break;
                        case 3:
                            pedaco_da_frase_com_a_palavra(palavra_procurada, 0, historia);
                            break;
                    }
                } while (opcao_c != 0);
                break;
            case 'd':
                do {
                    menu_d(&opcao_d);
                    switch (opcao_d) {
                        case 1:
                            printf("\nPosicao proxima ocorrencia:");
                            posicao_palavra_no_arquivo(palavra_procurada, i++);
                            break;
                        case 2:
                            pedaco_da_frase_com_a_palavra(palavra_procurada, j++, historia);
                            break;
                    }
                } while (opcao_d != 0);
                break;
        }
    } while (opcao != 'e');

    return 0;
}
