#include "0_input_check.h"
#include "2_i_sort.h"

#define MENU                                                    \
    "\nВыберите один из пунктов меню!"                          \
    "\n{1} Ввести данные для матрицы через консоль."            \
    "\n{2} Сгенерировать данные для матрицы случайным образом." \
    "\n{3} Заполнить матрицу данными из текстового файла."      \
    "\n{4} Выйти из программы.\n"                               

/* |ASSERT. Если утверждение не верно отображается отображается
 * информация об ошибке, также возвращается EXIT_FAILURE| */

#define ASSERT(condition)                                                      \
  do {                                                                         \
    if (!(condition)) {                                                        \
      std::cerr << "\t\t\t\tТЕСТ ПРОВАЛЕН!!!\n\tПричина: " #condition          \
                << " в файле " << __FILE__ << " строка " << __LINE__           \
                << std::endl;                                                  \
      std::exit(EXIT_FAILURE);                                                 \
    }                                                                          \
  } while (0)


enum main_choice{MANUAL_INPUT = 1, RANDOM_INPUT, TXT_INPUT, EXIT};

void input_rows_and_columns(int& rows, int& columns)
{
  InputCheck _input;
  std::cout << "Введите количество строк и столбцов для матрицы!\n"
    "Количество строк:";
  rows = _input.get_int();
  while (rows < 1) {
    std::cout << "Введите число больше 0:";
    rows = _input.get_int();
  }

  std::cout << "Количество столбцов:";
  columns = _input.get_int();
  while (columns < 1) {
    std::cout << "Введите число больше 0:";
    columns = _input.get_int();
  }
  std::cout << "\n";
}


void make_3_vec(int **matrix ,int rows, int columns, std::vector<int> &diagonal,
                std::vector<int> &upper, std::vector<int> &lower)
{
  
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      if (i == j) {
        diagonal.push_back(matrix[i][j]);
      }
      else if (i < j) {
        upper.push_back(matrix[i][j]);
      }
      else {
        lower.push_back(matrix[i][j]);
      }
    }
  }
}

void from_vec_to_matrix(int** &matrix, int rows, int columns, std::vector<int>& diagonal,
                        std::vector<int>& upper, std::vector<int>& lower) 
{
  int k1 = 0, k2 = 0, k3 = 0;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      if (i == j) {
        matrix[i][j] = diagonal[k1];
        k1++;
      }
      else if (i < j) {
        matrix[i][j] = upper[k2];
        k2++;
      }
      else {
        matrix[i][j] = lower[k3];
        k3++;
      }
    }
  }
}

void show_matrix(int** matrix, int rows, int columns)
{
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++)
      std::cout << matrix[i][j] << "\t";
    std::cout << std::endl;
  }
}

void swap_matrix(int**& matrix, int** copy_matrix, int rows, int columns)
{
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < columns; ++j) 
      matrix[i][j] = copy_matrix[i][j];
}

int main(void)
{
	setlocale(LC_ALL, "Russian");
	InputCheck _input;
  bubble_sort _bubble;
  selection_sort _selection;
  insertion_sort _insertion;
  shell_sort _shell;
  quick_sort _quick;
  const int begin_choice = 1, end_choice = 4;
  int choice = 0, rows = 0, columns = 0;
  // Приветствие 

  for (;;) {
    std::cout << MENU;
    choice = _input.get_int();

    while(begin_choice < choice && choice > end_choice) {
      std::cout << "Выберите один из пунктов!\n";
      choice = _input.get_int();
      std::cout << "\n";
    }
    choice = static_cast<main_choice>(choice);

    switch (choice) {
    case MANUAL_INPUT:
    {
      input_rows_and_columns(rows, columns);

      int** matrix{ new int* [rows] {} };
      for (int i = 0; i < rows; i++)
        matrix[i] = new int[columns] {};

      int** matrix_copy{ new int* [rows] {} };
      for (int i = 0; i < rows; i++)
        matrix_copy[i] = new int[columns] {};
      
      int num_comparisons = 0, num_permutations = 0;

      std::vector<int> diagonal;
      std::vector<int> upper;
      std::vector<int> lower;

      for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++) {
          std::cout << "Введите [" << (i + 1) << "," << (j + 1) << "] элемент матрицы: ";
          matrix[i][j] = _input.get_int();
          matrix_copy[i][j] = matrix[i][j];
        }

      


      make_3_vec(matrix, rows, columns, diagonal, upper, lower);

      std::cout << "\nИсходная матрица.\n";
      show_matrix(matrix, rows, columns);


      // bubble_sort
      _bubble.Sort(diagonal, num_comparisons, num_permutations, 1);
      _bubble.Sort(upper, num_comparisons, num_permutations, 0);
      _bubble.Sort(lower, num_comparisons, num_permutations, 1);

      std::cout << "\n\nСортировка пузырьком.\n"
                << "Количество сравнений: " << num_comparisons << std::endl 
                << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal, upper, lower);
      

      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);
      swap_matrix(matrix, matrix_copy, rows, columns);

      // selection_sort
      _selection.Sort(diagonal, num_comparisons, num_permutations, 1);
      _selection.Sort(upper, num_comparisons, num_permutations, 0);
      _selection.Sort(lower, num_comparisons, num_permutations, 1);

      std::cout << "\n\nСортировка отбором.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal, upper, lower);

      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);
      swap_matrix(matrix, matrix_copy, rows, columns);

      // insertion_sort
      _insertion.Sort(diagonal, num_comparisons, num_permutations, 1);
      _insertion.Sort(upper, num_comparisons, num_permutations, 0);
      _insertion.Sort(lower, num_comparisons, num_permutations, 1);

      std::cout << "\n\nСортировка вставкой.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal, upper, lower);
      
      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);
      swap_matrix(matrix, matrix_copy, rows, columns);

      // shell_sort
      _shell.Sort(diagonal, num_comparisons, num_permutations, 1);
      _shell.Sort(upper, num_comparisons, num_permutations, 0);
      _shell.Sort(lower, num_comparisons, num_permutations, 1);

      std::cout << "\n\nСортировка иетодом Шеллом.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal, upper, lower);

      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);
      swap_matrix(matrix, matrix_copy, rows, columns);

      // shell_sort
      _quick.Sort(diagonal, num_comparisons, num_permutations, 1);
      _quick.Sort(upper, num_comparisons, num_permutations, 0);
      _quick.Sort(lower, num_comparisons, num_permutations, 1);

      std::cout << "\n\nБыстрая сортировка.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal, upper, lower);

      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);
      swap_matrix(matrix, matrix_copy, rows, columns);

      for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
        delete[] matrix_copy[i];
      }
      delete[] matrix;
      delete[] matrix_copy;
      break;
    }
    case RANDOM_INPUT:
    {
      input_rows_and_columns(rows, columns);
      int** matrix{ new int* [rows] {} };
      for (int i = 0; i < rows; i++)
        matrix[i] = new int[columns] {};




      for (int i = 0; i < rows; i++)
        delete[] matrix[i];
      delete[] matrix;
      break;
    }
    case TXT_INPUT:
    {
      input_rows_and_columns(rows, columns);
      int** matrix{ new int* [rows] {} };
      for (int i = 0; i < rows; i++)
        matrix[i] = new int[columns] {};




      for (int i = 0; i < rows; i++)
        delete[] matrix[i];
      delete[] matrix;
      break;
      break;
    }
    case EXIT: return EXIT_SUCCESS;
    }
  }
}