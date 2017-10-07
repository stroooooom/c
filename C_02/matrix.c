#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

Matrix* create_matrix(int row, int col)
{
	M.row = row;
	M.col = col;
	M.element = (Element*) malloc(sizeof(Element) * row * col);
	if (M.element == NULL)
		return NULL;
	return &M;
}

Matrix* create_matrix_from_file(FILE* file)
{
	if (file == NULL)
		return NULL;
	if (fscanf(file, "%d %d", &M.row, &M.col) != 2)
		return NULL;
	if ((M.row < 1) || (M.col < 1))
		return NULL;
	M.element = (Element *) malloc(sizeof(Element) * M.row * M.col);
	if (M.element == NULL)
		return NULL;
	for(int i = 0; i < M.row; i++)
		for(int j = 0; j < M.col; j++)
		{
			if(fscanf(file, "%lf", &M.element[i*M.col+j].value) != 1)
				return NULL;
			M.element[i*M.col+j].row_id = i;
			M.element[i*M.col+j].col_id = j;
		}
	return &M;
}

int get_rows(Matrix* matrix)
{
	return matrix->row;
}

int get_cols(Matrix* matrix)
{
	return matrix->col;
}

void set_elem(Matrix* matrix, int row, int col, double val)
{
	if ( (row > 0) || (row < (matrix->row)) || (col > 0) || (col < matrix->col) )
		matrix->element[(matrix->col)*(row) + col].value = val;
}

double get_elem(Matrix* matrix, int row, int col)
{
	if ( (row > 0) || (row < (matrix->row)) || (col > 0) || (col < matrix->col) )
		return matrix->element[(matrix->col)*(row) + col].value;
	else
		return NaN;
}

void free_matrix(Matrix* matrix)
{
	free(matrix->element);
}
