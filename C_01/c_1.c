#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define No_Error 0
#define Input_Error -1
#define File_Error -2

int arglen(char *word);
int *countOccurrences(char *word, int word_len, char *filename, int *articleCount);
void cleanBuffer(char *buffer, int size);
int compare(char *str1, char *str2);
int disp(int *occr, int *artclCount);

int main(int agrc, char **argv)
{
	setbuf(stdout, NULL);
	if (agrc != 3)
	{
		printf("\nInput_Error: You must enter only 3 arguments");
		return Input_Error;
	}

    int word_len = arglen(argv[1]);
    char word[word_len];
    for(int i = 0; i < word_len; i++)
        word[i] = tolower(argv[1][i]);

    int articleCount = 0;
	int *n = countOccurrences(word, word_len, argv[2], &articleCount);
//	printf("\nacticle count = %d", articleCount);
	disp(n, &articleCount);
    printf("\n");
	return 0;
}

int *countOccurrences(char *word, int word_len, char *filename, int *articleCount)
{
	FILE *f = fopen(filename, "r");
	if (f == NULL)
		return NULL;

//	printf("\nword: %s", word);
//	printf("\nword_len = %d", word_len);
	char buffer[word_len];
	cleanBuffer(buffer, word_len);
	int b_id = 0;

	*articleCount = 1; //кол-во абзацев
	int occrCount = 0; // кол-во вхождений слова в абзац
	int *occr = (int*) malloc(*articleCount * sizeof(int));
	occr[*articleCount-1] = 0; //кол-во вхождений в слове по номеру абзаца

	char l = '*'; //letter
	char previous = '*';
	int res = 0;
	while(!feof(f))
	{
		previous = l;
		res = fscanf(f, "%c", &l);
		l = tolower(l);
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
				buffer[b_id] = l;
				b_id++;
			}
		else if ((ispunct(l) != 0) || (isspace(l) != 0))
		{
			occrCount += compare(buffer, word);
			cleanBuffer(buffer, word_len);
			b_id = 0;
		}

		if ((previous == '\n') && (l == '\n'))
		{
			occr[*articleCount-1] = occrCount;
			occrCount = 0;
			*articleCount += 1;
			occr = (int*) realloc(occr, *articleCount * sizeof(int));
			occr[*articleCount-1] = 0;
			cleanBuffer(buffer, word_len);
		}
	}
	occr[*articleCount-1] = occrCount;
//	printf("\n\nКол-во абзацев: %d", *articleCount);
//	printf("\nКол-во вхождений: ");
//	for(int i = 0; i < *articleCount; i++)
//		printf("\n#%d: %d", i, occr[i]);

	return occr;
}

int disp(int *occr, int *artclCount)
{
	float avg = 0;
	for(int i = 0; i < *artclCount; i++)
		avg +=occr[i];
//	printf("\nСумма вхождений: %d", (int) avg);
	avg /= *artclCount;
//	printf("\nСр. арифм. вхождений: %f", avg);
	float dispersion = 0;
	for(int i = 0; i < *artclCount; i++)
		dispersion += pow(occr[i]-avg, 2);
	if (*artclCount > 1)
		dispersion = sqrt(dispersion/(*artclCount-1));
	else
		dispersion = 0;
	printf("\nДисперсия вхождений: %f", dispersion);
	return dispersion;
}

int compare(char *str1, char *str2)
{
	if (strcmp(str1, str2) == 0)
		return 1;
	else
		return 0;
}

void cleanBuffer(char *buffer, int size)
{
	for(int i = 0; i < size; i++)
		buffer[i] = ' ';
}

int arglen(char *word)
{
	int length = 0;
	while(word[length])
		length++;
	return length;
}
