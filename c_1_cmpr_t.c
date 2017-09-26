#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define No_Error 0
#define Input_Error -1
#define File_Error -2

int length(char *word);
int printF(char *filename);
int *countOccurrences(char *word, int word_len, char *filename);
void cleanBuffer(char *buffer, int size);
int compare(char *str1, char *str2);

int main(int agrc, char **argv)
{
	if (agrc != 3)
	{
		printf("\nInput_Error: You must enter only 3 arguments");
		return Input_Error;
	}

    int word_len = length(argv[1]);
    char word[word_len];
    for(int i = 0; i < word_len; i++)
        word[i] = argv[1][i];
    
//   printF(argv[2]);
	int *n = countOccurrences(word, word_len, argv[2]);
    printf("\n");
	return 0;
}

void cleanBuffer(char *buffer, int size)
{
	for(int i = 0; i < size; i++)
		buffer[i] = ' ';
}

int *countOccurrences(char *word, int word_len, char *filename)
{
	FILE *f = fopen(filename, "r");
	if (f == NULL)
		return NULL;

    printf("\nword: %s", word);
	printf("\nword_len = %d", word_len);
	char buffer[word_len];
	cleanBuffer(buffer, word_len);
//	printf("\nclean buffer: %s", buffer);
	int b_id = 0;

	int articleCount = 1; //кол-во абзацев
	int occrCount = 0; // кол-во вхождений слова в абзац
	int *occr = (int*) malloc(articleCount * sizeof(int));
	occr[articleCount-1] = 0; //кол-во вхождений в слове по номеру абзаца

	char l; //letter
	char previous = '*';
	int res = 0;
	while(!feof(f))
	{
		previous = l;
		res = fscanf(f, "%c", &l);
		if (feof(f))
		{
			occrCount += compare(buffer, word);
			break;
		}
		else if ((ispunct(l) == 0) && (isspace(l) == 0))
			if (b_id < word_len)
			{
				buffer[b_id] = l;
				b_id++;
			}
			else
			{
				cleanBuffer(buffer, word_len);
				b_id = 0;
			//	printf("\nbuffer cleaned (b_id >= word_len)");
				buffer[b_id] = l;
				b_id++;
			}
		else if ((ispunct(l) != 0) || (isspace(l) != 0))
		{
			occrCount += compare(buffer, word);
            printf("compare(buffer, word) = %d", compare(word, buffer));
            printf("strcmp(buffer, word) = %d", strcmp(word, buffer));
            printf("\noccrCount = %d", occrCount);
			cleanBuffer(buffer, word_len);
			b_id = 0;
		//	printf("\nbuffer cleaned (is != 0)");
		}

		if ((previous == '\n') && (l == '\n'))
		{
			occr[articleCount-1] = occrCount;
			printf("\noccr[%d] = %d", occr[articleCount-1], occrCount);
			occrCount = 0;
			articleCount++;
			occr = (int*) realloc(occr, articleCount * sizeof(int));
			occr[articleCount-1] = 0;
			cleanBuffer(buffer, word_len);
		}
		printf("\n  curr l: %c", l);
		printf("  curr word: %s", buffer);
	//	printf("  ispunct(%c) = %d   ispunct(%c) = %d", l, ispunct(l), l, isspace(l));
	}
	occr[articleCount-1] = occrCount;
	printf("\n\nКол-во абзацев: %d", articleCount);
	printf("\nКол-во вхождений: ");
	for(int i = 0; i < articleCount; i++)
		printf("\n#%d: %d", i, occr[i]);
	return occr;
}


int compare(char *str1, char *str2)
{
	if (strcmp(str1, str2) == 0)
		return 1;
	else
		return 0;
}

int printF(char *filename)
{
	FILE *f = fopen(filename, "r");
	if (f == NULL)
	{
		printf("File_Error: File can not be found\n");
		return File_Error;
	}

	char l;
	while(!feof(f))
	{
		fscanf(f, "%c", &l);
		printf("%c", l);
		if (l == '\n')
			printf("(n)");
	}

	return No_Error;
}

int length(char *word)
{
	int length = 0;
	while(word[length])
		length++;
	return length;
}
