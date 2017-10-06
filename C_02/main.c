#include <stdio.h>
#include <math.h>
#include "matrix.h"

double euclidNorm(Matrix* M);

int main(int argc, char **agrv)
{
	if (argc > 1)
		for(int i = 1; i < argc; i++)
		{
			FILE *file = fopen(agrv[i], "r");
			if (file == NULL)
				printf("\n'%s': file was not found", agrv[i]);
			else
			{
				Matrix *M = create_matrix_from_file(file);
				if (M != NULL)
					printf("\n'%s': euclidian matrix norm is %g", agrv[i], euclidNorm(M));
				fclose(file);
				free_matrix(M);
			}
		}
	else
		printf("\nError: not enough arguments");
	return 0;
}

double euclidNorm(Matrix* M)
{
	double sum = 0;
	int rows = get_rows(M);
	int cols = get_cols(M);
	for(int i = 0; i < rows*cols; i++)
		sum += pow(M->element[i].value, 2);
	return sqrt(sum);
}
