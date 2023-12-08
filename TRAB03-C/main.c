#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

#define MAX_LINE_LENGTH 300

void flush_in();
char *get_next_line(int fd);
size_t ft_strlen(const char *s);
char *ft_strdup(const char *s1);
void read_file(const char *filename);
char *ft_strchr(const char *s, int c);
void display_inverted(const char *filename);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_substr_gnl(char const *s, unsigned int start, size_t len);
void search_in_inverted_file(const char *filename, const char *word);
void search_next_occurrence(const char *filename, const char *word, int start);

int main()
{
  char filename[100] = "historia.txt";

  char *word;
  int choice, start_position = 0;

  do
  {
    printf("\nMenu:\n");
    printf("1. Ler um arquivo texto\n");
    printf("2. Apresentar o arquivo invertido\n");
    printf("3. Procurar uma palavra no arquivo invertido\n");
    printf("4. Procurar a proxima ocorrencia\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%i", &choice);
    flush_in();

    switch (choice)
    {
    case 1:
      read_file(filename);
      break;
    case 2:
      display_inverted(filename);
      break;
    case 3:
      printf("Digite a palavra a ser procurada: ");
      scanf("%s", word);
      flush_in();
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

void read_file(const char *filename)
{
  FILE *file = fopen(filename, "r");
  char line[MAX_LINE_LENGTH];

  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo!\n");
    return;
  }

  printf("\nConteudo do arquivo:\n");
  while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
  {
    printf("%s", line);
  }

  fclose(file);
}

void display_inverted(const char *filename)
{
  FILE *file = fopen(filename, "r");
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo!\n");
    return;
  }

  printf("\nConteúdo do arquivo invertido:\n");
  while ((read = getline(&line, &len, file)) != EOF)
  {
    len = strlen(line);
    while (len != 0)
    {
      printf("%c", line[len]);
      len--;
    }
  }

  fclose(file);
}

void search_in_inverted_file(const char *filename, const char *word)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo!\n");
    return;
  }

  char *inverted_line = malloc(MAX_LINE_LENGTH);
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, file)) != EOF)
  {
    int word_len = strlen(word);
    int len = strlen(line);
    while (len != 0)
    {
      if(line[len] == word[0])
      {
        while(word_len != 0)
        {
          
          word_len--;
        
        }
      }
      len--;
    }
    inverted_line[len] = '\0';

    // Procurar a palavra
    char *ptr = inverted_line;
    while ((ptr = strstr(ptr, word)) != NULL)
    {
      printf("Palavra '%s' encontrada na pos: %ld\n", word, ptr - inverted_line);
      ptr += word_len;
    }
  }

  free(line);
  free(inverted_line);
  fclose(file);
}

void search_next_occurrence(const char *filename, const char *word, int start)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo!\\n");
    return;
  }

  char *line = malloc(MAX_LINE_LENGTH);
  char *inverted_line = malloc(MAX_LINE_LENGTH);
  int word_len = strlen(word);
  int line_num = 0;
  bool found = false;

  while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
  {
    line_num++;

    // Inverter a linha
    int len = strlen(line);
    for (int i = 0; i < len; i++)
    {
      inverted_line[i] = line[len - 1 - i];
    }
    inverted_line[len] = '\0';

    // Procurar a palavra na linha invertida
    if (line_num >= start)
    {
      char *ptr = inverted_line;
      while ((ptr = strstr(ptr, word)) != NULL)
      {
        int position = (int)(ptr - inverted_line);
        if (line_num > start || (line_num == start && position > start))
        {
          printf("Proxima ocorrencia da palavra '%s' encontrada na linha %d, pos: %d\n", word, line_num, position);
          start = line_num;
          found = true;
          break;
        }
        ptr += word_len;
      }
    }

    if (found)
    {
      break;
    }
  }

  if (!found)
  {
    printf("Nao foram encontradas mais ocorrencias da palavra '%s'.\n", word);
  }

  free(line);
  free(inverted_line);
  fclose(file);
}

static char *get_line(char **static_buffer)
{
  char *to_new_line;
  size_t line_size;
  char *line;
  char *temp_buffer;

  if (*static_buffer == NULL)
    return (NULL);
  to_new_line = ft_strchr(*static_buffer, '\n');
  if (to_new_line)
  {
    line_size = (to_new_line - *static_buffer) + 1;
    line = ft_substr_gnl(*static_buffer, 0, line_size);
    to_new_line++;
    temp_buffer = ft_strdup(to_new_line);
    free(*static_buffer);
    *static_buffer = ft_strdup(temp_buffer);
    free(temp_buffer);
    return (line);
  }
  else
    return (NULL);
}

static void assign_line(int bytes, char **stt_buffer, char **buf, char **line)
{
  char *temp;

  if (bytes > 0)
  {
    if (*stt_buffer == NULL)
      *stt_buffer = ft_strdup("");
    temp = ft_strjoin(*stt_buffer, *buf);
    free(*stt_buffer);
    *stt_buffer = ft_strdup(temp);
    free(temp);
    *line = get_line(stt_buffer);
  }
  free(*buf);
  if (bytes <= 0 && *stt_buffer != NULL)
  {
    if (**stt_buffer != '\0')
      *line = ft_strdup(*stt_buffer);
    free(*stt_buffer);
    *stt_buffer = NULL;
  }
}

char *get_next_line(int fd)
{
  char *line;
  char *buffer;
  int bytes_read;
  static char *static_buffer;

  if (fd < 0 || MAX_LINE_LENGTH <= 0)
    return (NULL);
  line = get_line(&static_buffer);
  while (line == NULL)
  {
    buffer = malloc((MAX_LINE_LENGTH + 1) * sizeof(char));
    if (buffer == NULL)
      return (NULL);
    bytes_read = read(fd, buffer, MAX_LINE_LENGTH);
    if (bytes_read < 0)
    {
      free(buffer);
      return (NULL);
    }
    buffer[bytes_read] = '\0';
    assign_line(bytes_read, &static_buffer, &buffer, &line);
    if (bytes_read <= 0 && static_buffer == NULL)
      break;
  }
  return (line);
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

char *ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
  char *lenstr;
  size_t lens;
  unsigned int i;

  i = 0;
  if (!s)
    return (NULL);
  lens = ft_strlen(s);
  if (start >= lens)
    return (ft_strdup(""));
  lens = ft_strlen(s + start);
  if (lens < len)
    len = lens;
  lenstr = (char *)malloc((len + 1) * sizeof(char));
  if (!lenstr)
    return (NULL);
  while (start != len)
  {
    lenstr[i] = s[start];
    i++;
    start++;
  }
  lenstr[i] = '\0';
  return (lenstr);
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

void flush_in()
{
  int ch;
  while ((ch = fgetc(stdin)) != EOF && ch != '\n')
  {
  }
}
