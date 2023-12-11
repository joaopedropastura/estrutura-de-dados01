#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *word;
    int count;
    int *positions;
} WordInfo;

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' && s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i ++;
	}
	if (n == i)
		return (0);
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

WordInfo createWordInfo(const char *word, int position)
{
    WordInfo wi;
    wi.word = strdup(word); // Duplica a string.
    wi.count = 1;
    wi.positions = (int *)malloc(sizeof(int)); // Aloca espaço para uma posição.
    wi.positions[0] = position;
    return wi;
}

void createListWordInfo(WordInfo **wordInfo, char **words)
{
    int i = 0;
    while (words[i] != NULL)
    {
        int found = 0;
        int j = 0;
        // Verifica se a lista já contém elementos antes de tentar acessá-los.
        while (*wordInfo != NULL && (*wordInfo)[j].word != NULL)
        {
            if (ft_strncmp((*wordInfo)[j].word, words[i], strlen(words[i])) == 0)
            {
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
            *wordInfo = (WordInfo *)realloc(*wordInfo, sizeof(WordInfo) * (i + 1));
            (*wordInfo)[i] = createWordInfo(words[i], i);
        }
        i++;
    }
    // Adiciona o marcador de fim da lista.
    *wordInfo = (WordInfo *)realloc(*wordInfo, sizeof(WordInfo) * (i + 1));
    (*wordInfo)[i].word = NULL; // Indica o final da lista.
}

void freeWordInfoList(WordInfo *wordInfo)
{
    if (wordInfo == NULL)
        return;
    int i = 0;
    while (wordInfo[i].word != NULL)
    {
        free(wordInfo[i].word);
        free(wordInfo[i].positions);
        i++;
    }
    free(wordInfo);
}

int main()
{
    char *words[] = {"apple", "banana", "apple", NULL};
    WordInfo *wordInfo;
    wordInfo->word = NULL;
    wordInfo->count = 0;
    wordInfo->positions = NULL;

    createListWordInfo(&wordInfo, words);
    int i = 0;

    printf("WordInfo:\n");
    while (wordInfo[i].word != NULL)
    {
        printf("Word: %s\n", wordInfo[i].word);
        printf("Count: %d\n", wordInfo[i].count);
        printf("Positions: ");
        for (int j = 0; j < wordInfo[i].count; j++)
        {
            printf("%d ", wordInfo[i].positions[j]);
        }
        printf("\n\n");
        i++;
    }
    // ... (usar wordInfo aqui)

    // Libera a memória.
    freeWordInfoList(wordInfo);

    return 0;
}