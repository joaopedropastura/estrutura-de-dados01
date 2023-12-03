#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 300

void read_file(const char *filename);
void display_inverted(const char *filename);
void search_in_inverted_file(const char *filename, const char *word);
void search_next_occurrence(const char *filename, const char *word, int start);

int main() {
    char filename[100] = "historia.txt", word[100];
    int choice, start_position = 0;

    do {
        printf("\nMenu:\n");
        printf("1. Ler um arquivo texto\n");
        printf("2. Apresentar o arquivo invertido\n");
        printf("3. Procurar uma palavra no arquivo invertido\n");
        printf("4. Procurar a proxima ocorrencia\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                read_file(filename);
                break;
            case 2:
                display_inverted(filename);
                break;
            case 3:
                printf("Digite a palavra a ser procurada: ");
                scanf("%s", word);
                search_in_inverted_file(filename, word);
                start_position = 0;
                break;
            case 4:
                search_next_occurrence(filename, word, start_position);
                break;
            case 5:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (choice != 5);

    return 0;
}

void read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    char line[MAX_LINE_LENGTH];

    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("\nConteudo do arquivo:\n");
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}

void display_inverted(const char *filename) {
    FILE *file = fopen(filename, "r");
    char line[MAX_LINE_LENGTH];
    int i, len;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("\nConteúdo do arquivo invertido:\n");
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        len = strlen(line);
        for (i = len - 1; i >= 0; i--) {
            printf("%c", line[i]);
        }
    }

    fclose(file);
}

void search_in_inverted_file(const char *filename, const char *word) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char *line = malloc(MAX_LINE_LENGTH);
    char *inverted_line = malloc(MAX_LINE_LENGTH);
    int word_len = strlen(word);

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        // Inverter a linha
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            inverted_line[i] = line[len - 1 - i];
        }
        inverted_line[len] = '\0';

        // Procurar a palavra
        char *ptr = inverted_line;
        while ((ptr = strstr(ptr, word)) != NULL) {
            printf("Palavra '%s' encontrada na pos: %ld\n", word, ptr - inverted_line);
            ptr += word_len;
        }
    }

    free(line);
    free(inverted_line);
    fclose(file);
}

void search_next_occurrence(const char *filename, const char *word, int start) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\\n");
        return;
    }

    char *line = malloc(MAX_LINE_LENGTH);
    char *inverted_line = malloc(MAX_LINE_LENGTH);
    int word_len = strlen(word);
    int line_num = 0;
    bool found = false;

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        line_num++;

        // Inverter a linha
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            inverted_line[i] = line[len - 1 - i];
        }
        inverted_line[len] = '\0';

        // Procurar a palavra na linha invertida
        if (line_num >= start) {
            char *ptr = inverted_line;
            while ((ptr = strstr(ptr, word)) != NULL) {
                int position = (int)(ptr - inverted_line);
                if (line_num > start || (line_num == start && position > start)) {
                    printf("Proxima ocorrencia da palavra '%s' encontrada na linha %d, pos: %d\n", word, line_num, position);
                    start = line_num;
                    found = true;
                    break;
                }
                ptr += word_len;
            }
        }

        if (found) {
            break;
        }
    }

    if (!found) {
        printf("Nao foram encontradas mais ocorrencias da palavra '%s'.\n", word);
    }

    free(line);
    free(inverted_line);
    fclose(file);
}