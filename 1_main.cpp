#include "0_input_check.h"

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





int main(void)
{
	setlocale(LC_ALL, "Russian");
	InputCheck _input;
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

      for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++) {
          std::cout << "Введите [" << (i + 1) << "," << (j + 1) << "] элемент матрицы: ";
          std::cin >> matrix[i][j];
        }


      std::cout << "\nИсходная матрица:\n";
      for (int i = 0; i < rows; i++)
      {
        // выводим данные столбцов i-й строки
        for (int j = 0; j < columns; j++)
        {
          std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
      }












      std::cout << "\nОтфильтрованная матрица:\n";
      for (int i = 0; i < rows; i++)
      {
        for (int j = 0; j < columns; j++)
        {
          std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
      }

      for (int i = 0; i < rows; i++)
        delete[] matrix[i];
      delete[] matrix;
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