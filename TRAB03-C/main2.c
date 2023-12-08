#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 128

typedef struct Post {
    int docID;             
    struct Post *next;
} Post;

typedef struct Term {
    char *word;            
    Post *postings;        
    struct Term *next;     
} Term;

typedef struct InvertedIndex {
    Term *terms;
} InvertedIndex;



void read_file(const char *filename);


void display_inverted(const char *filename);

char *file_to_lower_case(const char *filename);


char *ft_strchr(const char *s, int c);
size_t ft_strlen(const char *s);
char *ft_strdup(const char *s1);
char *ft_strjoin(char const *s1, char const *s2);




char *file_to_lower_case(const char *filename) {
    FILE *file = fopen(filename, "r");
    char *line;
    char *result;
    char *lower_line;
    size_t len = 0;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    int  i = 0;
    while (getline(&line, &len, file) != EOF) {
        while(line[i] != '\0') {
            line[i] = tolower(line[i]);
            lower_line = ft_strjoin(lower_line, line[i]);
            i++;
        }
        result = ft_strjoin(result, lower_line);
    }
    fclose(file);
    return result;
}

void print_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    char *line;
    size_t len = 0;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    while (getline(&line, &len, file) != EOF) {
        printf("%s", line);
    }

    fclose(file);
}



char *ft_strjoin(char const *s1, char const *s2)
{
  size_t size;
  char *len;
  int i;
  int j;

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

size_t ft_strlen(const char *s)
{
  size_t i;

  i = 0;
  while (s[i] != '\0')
  {
    i++;
  }
  return (i);
}

char *ft_strdup(const char *s1)
{
  char *str;
  unsigned int len;
  unsigned int i;

  len = ft_strlen(s1);
  i = 0;
  str = malloc(len + 1 * sizeof(char));
  if (str == NULL)
    return (NULL);
  while (len > i)
  {
    str[i] = s1[i];
    i++;
  }
  str[i] = '\0';
  return (str);
}

char *ft_strchr(const char *s, int c)
{
  size_t i;

  i = 0;
  while (s[i] != '\0')
  {
    if (s[i] == (unsigned char)c)
      return ((char *)&s[i]);
    i++;
  }
  if (c == '\0')
    return ((char *)&s[i]);
  return (NULL);
}


int main()
{
    char *filename = "./historia.txt";

    char *res = file_to_lower_case(filename);
    print_file(res);
}