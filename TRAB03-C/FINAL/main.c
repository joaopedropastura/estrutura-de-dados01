#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define true 1

typedef struct
{
    char *word;
    int count;
    int *positions;
} WordInfo;

int menu();
void flush_in();
size_t ft_strlen(const char *s);
char *text_to_lower(char *filename);
char *ft_strjoin(char *s1, char *s2);
void printWordInfoList(WordInfo *wordInfoArray);
void writeToFile(WordInfo *wordInfoArray, char *filename);
void createListWordInfo(WordInfo **wordInfo, char **words);
WordInfo createWordInfo(char *word, int position, int count);
char **separate_words(char *lower_text, const char *delimiters);
void searchWord(WordInfo *wordInfo, char **words, const char *searchWord, int context);
void searchLogFile(char *filename, char *searchWord);

int main()
{
    WordInfo *wordInfo = (WordInfo *)malloc(sizeof(WordInfo) * 1);
    wordInfo->word = NULL;
    wordInfo->count = 0;
    wordInfo->positions = NULL;

    char *file = "../db/historia.txt";
    char *file_to_lower = NULL;
    char **words = NULL;
    const char delimiters[] = " ,.!?;:\n\t";

    char word[100];
    while (true)
    {
        switch (menu())
        {
        case 0:
            file_to_lower = text_to_lower(file);
            words = separate_words(file_to_lower, delimiters);
            break;
        case 1:
            createListWordInfo(&wordInfo, words);
            writeToFile(wordInfo, "../db/result/log.txt");
            printWordInfoList(wordInfo);
            break;
        case 2:
            printf("Digite a palavra a ser procurada: ");
            scanf("%s", word);
            searchLogFile("../db/result/log.txt", word);

            break;
        case 3:
            printf("Digite a palavra a ser procurada: ");
            scanf("%s[^\n]", word);
            searchWord(wordInfo, words, word, 3);
            break;
        
        default:
            printf("Opção inválida.\n");
            break;
        }
    }

    // Liberação de memória e limpeza
    free(file_to_lower);
    return 0;
}

int menu()
{
    int option = 0;
    printf("\nTRABALHO 03\n");
    printf("----- DIGITE O NUMERO DA OPCAO DESEJADA -----\n");
    printf("{00} - Para ler o arquivo texto \n");
    printf("{01} - Apresentar o arquivo invertido \n");
    printf("{02} - Procurar uma palavra no arquivo invertido \n");
    printf("{03} - Mostrar o contexto de uma palavra \n");
    printf("Digite uma opcao: ");
    scanf("%i", &option);
    // flush_in();
    return option;
}

void flush_in()
{
    int ch;
    while ((ch = fgetc(stdin)) != EOF && ch != '\n')
    {
    }
}

void printSentences(char **sentences)
{
    int i = 0;
    while (sentences[i] != NULL)
    {
        printf("%s\n", sentences[i]);
        i++;
    }
}

void searchLogFile(char *filename, char *searchWord) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s!\n", filename);
        return;
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;

    while ((read = getline(&line, &len, file)) != -1) 
    {
        if (strstr(line, searchWord) != NULL) 
        {
            printf("%s", line);
            return;
        }
    }

    if (ferror(file)) {
        printf("Erro ao ler o arquivo %s!\n", filename);
    }

    free(line);
    fclose(file);
}

void searchWord(WordInfo *wordInfo, char **words, const char *searchWord, int context)
{
    int i = 0;
    while (wordInfo[i].word != NULL)
    {
        if (strcmp(wordInfo[i].word, searchWord) == 0)
        {
            for (int j = 0; j < wordInfo[i].count; j++)
            {
                int position = wordInfo[i].positions[j];
                // Exibir contexto
                int start = position - context;
                int end = position + context;
                start = start < 0 ? 0 : start;
                printf("Contexto para '%s' (Pos %d): ", searchWord, position);
                for (int k = start; k <= end; k++)
                {
                    if (words[k] != NULL)
                    {
                        printf("%s ", words[k]);
                    }
                }
                printf("\n");
            }
            return;
        }
        i++;
    }
    printf("Palavra '%s' não encontrada.\n", searchWord);
}

void printWordInfoList(WordInfo *wordInfoArray)
{
    int i = 0;
    while (wordInfoArray[i].word != NULL)
    {
        printf("Word: %s, Count: %d, Positions: ", wordInfoArray[i].word, wordInfoArray[i].count);
        for (int j = 0; j < wordInfoArray[i].count; j++)
        {
            printf("%d ", wordInfoArray[i].positions[j]);
        }
        printf("\n");
        i++;
    }
}

void writeToFile(WordInfo *wordInfoArray, char *filename)
{
    FILE *file = fopen(filename, "w");
    int i = 0;
    while (wordInfoArray[i].word != NULL)
    {
        fprintf(file, "Word: %s, Count: %d, Positions: ", wordInfoArray[i].word, wordInfoArray[i].count);
        for (int j = 0; j < wordInfoArray[i].count; j++)
        {
            fprintf(file, "%d ", wordInfoArray[i].positions[j]);
        }
        fprintf(file, "\n");
        i++;
    }
    fclose(file);
}

void createListWordInfo(WordInfo **wordInfo, char **words)
{
    int i = 0;
    while (words[i] != NULL)
    {
        int found = 0;
        int j = 0;
        while ((*wordInfo)[j].word != NULL)
        {
            if (strcmp((*wordInfo)[j].word, words[i]) == 0)
            {
                // Palavra encontrada, atualizar contagem e posições
                (*wordInfo)[j].count++;
                (*wordInfo)[j].positions = (int *)realloc((*wordInfo)[j].positions, sizeof(int) * (*wordInfo)[j].count);
                (*wordInfo)[j].positions[(*wordInfo)[j].count - 1] = i;
                found = 1;
                break;
            }
            j++;
        }
        if (!found)
        {
            // Palavra não encontrada, adicionar nova WordInfo
            (*wordInfo) = (WordInfo *)realloc(*wordInfo, sizeof(WordInfo) * (j + 2));
            (*wordInfo)[j] = createWordInfo(words[i], i, 1);
            (*wordInfo)[j + 1].word = NULL;
        }
        i++;
    }
}

WordInfo createWordInfo(char *word, int position, int count)
{
    WordInfo wordInfo;

    wordInfo.count = count;
    wordInfo.positions = (int *)malloc(sizeof(int) * count);
    wordInfo.word = (char *)malloc(sizeof(char) * ft_strlen(word) + 1);

    wordInfo.positions[count - 1] = position;

    for (int j = 0; j < ft_strlen(word); j++)
        wordInfo.word[j] = word[j];
    wordInfo.word[ft_strlen(wordInfo.word)] = '\0';

    return wordInfo;
}

char **separate_words(char *lower_text, const char *delimiters)
{
    char **words;
    int word_count = 0;
    char *word;
    char *temp_text = strdup(lower_text);

    word = strtok(temp_text, delimiters);
    while (word != NULL)
    {
        word_count++;
        word = strtok(NULL, delimiters);
    }
    words = malloc(sizeof(char *) * (word_count + 1));
    strcpy(temp_text, lower_text);
    word = strtok(temp_text, delimiters);
    int i = 0;
    while (word != NULL)
    {
        words[i] = strdup(word);
        word = strtok(NULL, delimiters);
        i++;
    }
    words[i] = NULL;

    free(temp_text);
    return words;
}

char *ft_strjoin(char *s1, char *s2)
{
    size_t size;
    char *len;
    int i;
    int j;

    if (s1 == NULL || s2 == NULL)
        return "";

    i = 0;
    j = 0;
    size = ft_strlen(s1) + ft_strlen(s2);
    len = malloc(size + 1 * sizeof(char));
    if (len == NULL)
        return (NULL);
    while (s1[i] != '\0')
    {
        len[i] = s1[i];
        i++;
    }
    while (s2[j] != '\0')
    {
        len[i] = s2[j];
        i++;
        j++;
    }
    len[i] = '\0';
    return (len);
}

char *text_to_lower(char *filename)
{
    FILE *file = fopen(filename, "r");
    char *text_to_lower = "";
    char *line = NULL;
    size_t len = 0;
    size_t read;

    while ((read = getline(&line, &len, file)) != EOF)
    {
        if (line == NULL || line[0] == '\n' || line[0] == '\0' || line[0] == '\t' || line[0] == '\r')
            continue;
        char *lower_line = (char *)malloc(sizeof(char) * len + 1);
        if (lower_line == NULL)
            return "erro ao alocar memoria";
        int i = 0;
        while (line[i] != '\n')
        {
            lower_line[i] = tolower(line[i]);
            i++;
        }
        lower_line[i] = '\0';
        text_to_lower = ft_strjoin(text_to_lower, lower_line);
    }

    free(line);
    fclose(file);
    return text_to_lower;
}

size_t ft_strlen(const char *s)
{
    size_t i = 0;

    while (s[i] != '\0')
        i++;
    return (i);
}