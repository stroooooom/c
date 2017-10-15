#include <math.h>
#include "matrix.h"

#define ERROR_ARG "\nError: not enough arguments"

double euclidNorm(Matrix* M);

int main(int argc, char **agrv)
{
	if (argc <= 1)
	{
		printf(ERROR_ARG);
		return 1;
	}
	for (int i = 1; i < argc; i++)
	{
		FILE *file = fopen(agrv[i], "r");
		if (!file)
		{
			printf("\n'%s': file was not found", agrv[i]);
			continue;
		}
		Matrix *matrix = create_matrix_from_file(file);
		if (matrix)
		{
			printf("\n'%s': euclidian matrix norm is %g", agrv[i], euclidNorm(matrix));
		}
		else
		{
			printf("\n'%s': error while creating this matrix", agrv[i]);
		}
		fclose(file);
		free_matrix(matrix);
	}
	return 0;
}

double euclidNorm(Matrix* matrix)
{
	double sum = 0.0;
	int rows = get_rows(matrix);
	int cols = get_cols(matrix);
	for (int i = 0; i < rows * cols; i++)
		sum += matrix->element[i].value * matrix->element[i].value;
	return sqrt(sum);
}
