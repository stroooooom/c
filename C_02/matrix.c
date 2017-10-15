#include "matrix.h"

Matrix* create_matrix(int row, int col)
{
	Matrix matrix;
	matrix.rows = row;
	matrix.cols = col;
	matrix.element = (Element*) malloc(sizeof(Element) * row * col);
	if (matrix.element == NULL)
		return NULL;
	Matrix *matrix_ptr = (Matrix*) malloc(sizeof(Matrix));
	*matrix_ptr = matrix;
	return matrix_ptr;
}

Matrix* create_matrix_from_file(FILE* file)
{
	Matrix matrix;
	if (file == NULL)
		return NULL;
	if (fscanf(file, "%d %d", &matrix.rows, &matrix.cols) != 2)
		return NULL;
	if ((matrix.rows < 1) || (matrix.cols < 1))
		return NULL;
	matrix.element = (Element *) malloc(sizeof(Element) * matrix.rows * matrix.cols);
	if (matrix.element == NULL)
		return NULL;
	for(int i = 0; i < matrix.rows; i++)
		for (int j = 0; j < matrix.cols; j++)
		{
			if(fscanf(file, "%lf", &matrix.element[i * matrix.cols + j].value) != 1)
				return NULL;
			matrix.element[i * matrix.cols + j].row = i;
			matrix.element[i * matrix.cols + j].col = j;
		}
	Matrix *matrix_ptr = (Matrix*) malloc(sizeof(Matrix));
	*matrix_ptr = matrix;
	return matrix_ptr;
}

int get_rows(Matrix* matrix)
{
	return matrix->rows;
}

int get_cols(Matrix* matrix)
{
	return matrix->cols;
}

void set_elem(Matrix* matrix, int row, int col, double val)
{
	if ( (row >= 0) && (row < (matrix->rows)) && (col >= 0) && (col < matrix->cols) )
		matrix->element[matrix->cols * row + col].value = val;
}

double get_elem(Matrix* matrix, int row, int col)
{
	if ( (row >= 0) || (row < (matrix->rows)) || (col >= 0) || (col < matrix->cols) )
		return matrix->element[matrix->cols * row + col].value;
	else
		return 0;
}

void free_matrix(Matrix* matrix)
{
	free(matrix->element);
	free(matrix);
}
