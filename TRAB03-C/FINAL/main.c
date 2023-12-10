#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS 100


typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
    int positions[MAX_WORDS];
} WordInfo;


size_t ft_strlen(const char *s);
char *text_to_lower(char *filename);
char *ft_strjoin(char *s1, char *s2);
char delimiters[] = " ,.!?;:\n\t";

int main()
{
    char *file = {"../db/historia.txt"};
    char *file_to_lower = text_to_lower(file);

    return 0;
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
        if(line == NULL || line[0] == '\n' || line[0] == '\0' || line[0] == '\t' || line[0] == '\r')
            continue;
        char *lower_line = (char *)malloc(sizeof(char) * len + 1);
        if(lower_line == NULL)
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