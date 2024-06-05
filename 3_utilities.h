#include "2_i_sort.h"

void input_rows_and_columns(int& rows, int& columns);

void make_3_vec(int** matrix, int rows, int columns, std::vector<int>& diagonal,
  std::vector<int>& upper, std::vector<int>& lower);

void from_vec_to_matrix(int**& matrix, int rows, int columns, std::vector<int>& diagonal,
  std::vector<int>& upper, std::vector<int>& lower);

void show_matrix(int** matrix, int rows, int columns);

void swap_matrix(int** original, int** copy, int rows, int cols);

void save_to_file(int **matrix, int rows, int cols);

void save_to_file(int** matrix, int **matrix_copy, int rows, int cols, std::vector<int> com_and_per);