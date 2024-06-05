#include "3_utilities.h"

#define GREETING                                                                       \
    "Здравствуйте!\n"                                                                  \
    "Курсовая работа по дисциплине \"Информационные технологии и программирование\"\n" \
    "Выполнил: Щербаков Сергей Игоревич, группа 4304\n"                                \
    "Вариант 27\n"                                                                     \
    "Задача: Упорядочить главную диагональ матрицы по возрастанию,\n"                  \
    "        данные сверху от главной диагонали упорядочить по убыванию,\n"            \
    "        снизу от главной диагонали по возрастанию.\n\n"

#define MENU                                                    \
    "\nВыберите один из пунктов меню!"                          \
    "\n{1} Ввести данные для матрицы через консоль."            \
    "\n{2} Сгенерировать данные для матрицы случайным образом." \
    "\n{3} Заполнить матрицу данными из текстового файла."      \
    "\n{4} Выйти из программы.\n"                               



enum main_choice{MANUAL_INPUT = 1, RANDOM_INPUT, TXT_INPUT, EXIT};


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
  std::cout << GREETING;


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

      std::vector<int> diagonal_1, diagonal_2, diagonal_3, diagonal_4, diagonal_5;
      std::vector<int> upper_1, upper_2, upper_3, upper_4, upper_5;
      std::vector<int> lower_1, lower_2, lower_3, lower_4, lower_5;

      for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++) {
          std::cout << "Введите [" << (i + 1) << "," << (j + 1) << "] элемент матрицы: ";
          matrix[i][j] = _input.get_int();
          matrix_copy[i][j] = matrix[i][j];
        }

      save_to_file(matrix, rows, columns);
      

      make_3_vec(matrix, rows, columns, diagonal_1, upper_1, lower_1);
      make_3_vec(matrix, rows, columns, diagonal_2, upper_2, lower_2);
      make_3_vec(matrix, rows, columns, diagonal_3, upper_3, lower_3);
      make_3_vec(matrix, rows, columns, diagonal_4, upper_4, lower_4);
      make_3_vec(matrix, rows, columns, diagonal_5, upper_5, lower_5);


      std::cout << "\nИсходная матрица.\n";
      show_matrix(matrix, rows, columns);


      // bubble_sort
      _bubble.Sort(diagonal_1, num_comparisons, num_permutations, 1);
      _bubble.Sort(upper_1, num_comparisons, num_permutations, 100);
      _bubble.Sort(lower_1, num_comparisons, num_permutations, 1);

      std::cout << "\n\nСортировка пузырьком.\n"
                << "Количество сравнений: " << num_comparisons << std::endl 
                << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal_1, upper_1, lower_1);
      

      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);
      std::vector<int> com_and_per;
      com_and_per.push_back(num_comparisons);
      com_and_per.push_back(num_permutations);


      num_comparisons = 0, num_permutations = 0;

      // selection_sort
      _selection.Sort(diagonal_2, num_comparisons, num_permutations, 1);
      _selection.Sort(upper_2, num_comparisons, num_permutations, 100);
      _selection.Sort(lower_2, num_comparisons, num_permutations, 1);

      std::cout << "\n\nСортировка отбором.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal_2, upper_2, lower_2);

      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);
      com_and_per.push_back(num_comparisons);
      com_and_per.push_back(num_permutations);

      num_comparisons = 0, num_permutations = 0;

      // insertion_sort
      _insertion.Sort(diagonal_3, num_comparisons, num_permutations, 1);
      _insertion.Sort(upper_3, num_comparisons, num_permutations, 100);
      _insertion.Sort(lower_3, num_comparisons, num_permutations, 1);

      
      std::cout << "\n\nСортировка вставкой.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal_3, upper_3, lower_3);

      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);
      com_and_per.push_back(num_comparisons);
      com_and_per.push_back(num_permutations);

      num_comparisons = 0, num_permutations = 0;

      // shell_sort
      _shell.Sort(diagonal_4, num_comparisons, num_permutations, 1);
      _shell.Sort(upper_4, num_comparisons, num_permutations, 100);
      _shell.Sort(lower_4, num_comparisons, num_permutations, 1);

      std::cout << "\n\nСортировка методом Шелла.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal_4, upper_4, lower_4);

      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);
      com_and_per.push_back(num_comparisons);
      com_and_per.push_back(num_permutations);

      num_comparisons = 0, num_permutations = 0;

      // qs
      _quick.Sort(diagonal_5, num_comparisons, num_permutations, 1);
      _quick.Sort(upper_5, num_comparisons, num_permutations, 100);
      _quick.Sort(lower_5, num_comparisons, num_permutations, 1);

      std::cout << "\n\nБыстрая сортировка.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal_5, upper_5, lower_5);
      com_and_per.push_back(num_comparisons);
      com_and_per.push_back(num_permutations);
      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);

      save_to_file(matrix, matrix_copy, rows, columns, com_and_per);

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

      int** matrix_copy{ new int* [rows] {} };
      for (int i = 0; i < rows; i++)
        matrix_copy[i] = new int[columns] {};


      int num_comparisons = 0, num_permutations = 0, lower_bound = 0, upper_bound = 0;
      std::vector<int> diagonal_1, diagonal_2, diagonal_3, diagonal_4, diagonal_5;
      std::vector<int> upper_1, upper_2, upper_3, upper_4, upper_5;
      std::vector<int> lower_1, lower_2, lower_3, lower_4, lower_5;

      
      std::cout << "\nВведите нижнюю границу диапазона: ";
      lower_bound = _input.get_int();
      std::cout << "\nВведите верхнюю границу диапазона: ";
      upper_bound = _input.get_int();

      while (lower_bound >= upper_bound) {
        std::cout << "Неверно задан диапазон, повторите попытку!\n";
        std::cout << "\nВведите нижнюю границу диапазона: ";
        lower_bound = _input.get_int();
        std::cout << "\nВведите верхнюю границу диапазона: ";
        upper_bound = _input.get_int();
      }

      srand(static_cast<unsigned int>(time(0)));

      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
          matrix[i][j] = lower_bound + rand() % (upper_bound - lower_bound + 1);
          matrix_copy[i][j] = matrix[i][j];
        }
      }

      show_matrix(matrix, rows, columns);

      save_to_file(matrix, rows, columns);


      make_3_vec(matrix, rows, columns, diagonal_1, upper_1, lower_1);
      make_3_vec(matrix, rows, columns, diagonal_2, upper_2, lower_2);
      make_3_vec(matrix, rows, columns, diagonal_3, upper_3, lower_3);
      make_3_vec(matrix, rows, columns, diagonal_4, upper_4, lower_4);
      make_3_vec(matrix, rows, columns, diagonal_5, upper_5, lower_5);


      std::cout << "\nИсходная матрица.\n";
      show_matrix(matrix, rows, columns);


      // bubble_sort
      _bubble.Sort(diagonal_1, num_comparisons, num_permutations, 1);
      _bubble.Sort(upper_1, num_comparisons, num_permutations, 100);
      _bubble.Sort(lower_1, num_comparisons, num_permutations, 1);

      std::cout << "\n\nСортировка пузырьком.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal_1, upper_1, lower_1);


      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);
      std::vector<int> com_and_per;
      com_and_per.push_back(num_comparisons);
      com_and_per.push_back(num_permutations);


      num_comparisons = 0, num_permutations = 0;

      // selection_sort
      _selection.Sort(diagonal_2, num_comparisons, num_permutations, 1);
      _selection.Sort(upper_2, num_comparisons, num_permutations, 100);
      _selection.Sort(lower_2, num_comparisons, num_permutations, 1);

      std::cout << "\n\nСортировка отбором.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal_2, upper_2, lower_2);

      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);
      com_and_per.push_back(num_comparisons);
      com_and_per.push_back(num_permutations);

      num_comparisons = 0, num_permutations = 0;

      // insertion_sort
      _insertion.Sort(diagonal_3, num_comparisons, num_permutations, 1);
      _insertion.Sort(upper_3, num_comparisons, num_permutations, 100);
      _insertion.Sort(lower_3, num_comparisons, num_permutations, 1);


      std::cout << "\n\nСортировка вставкой.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal_3, upper_3, lower_3);

      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);
      com_and_per.push_back(num_comparisons);
      com_and_per.push_back(num_permutations);

      num_comparisons = 0, num_permutations = 0;

      // shell_sort
      _shell.Sort(diagonal_4, num_comparisons, num_permutations, 1);
      _shell.Sort(upper_4, num_comparisons, num_permutations, 100);
      _shell.Sort(lower_4, num_comparisons, num_permutations, 1);

      std::cout << "\n\nСортировка методом Шелла.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal_4, upper_4, lower_4);

      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);
      com_and_per.push_back(num_comparisons);
      com_and_per.push_back(num_permutations);

      num_comparisons = 0, num_permutations = 0;

      // qs
      _quick.Sort(diagonal_5, num_comparisons, num_permutations, 1);
      _quick.Sort(upper_5, num_comparisons, num_permutations, 100);
      _quick.Sort(lower_5, num_comparisons, num_permutations, 1);

      std::cout << "\n\nБыстрая сортировка.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal_5, upper_5, lower_5);
      com_and_per.push_back(num_comparisons);
      com_and_per.push_back(num_permutations);
      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);

      save_to_file(matrix, matrix_copy, rows, columns, com_and_per);

      for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
        delete[] matrix_copy[i];
      }
      delete[] matrix;
      delete[] matrix_copy;

      break;
    }
    case TXT_INPUT:
    {
      input_rows_and_columns(rows, columns);

      int** matrix{ new int* [rows] {} };
      for (int i = 0; i < rows; i++)
        matrix[i] = new int[columns] {};

      int** matrix_copy{ new int* [rows] {} };
      for (int i = 0; i < rows; i++)
        matrix_copy[i] = new int[columns] {};


      int num_comparisons = 0, num_permutations = 0;
      std::vector<int> diagonal_1, diagonal_2, diagonal_3, diagonal_4, diagonal_5;
      std::vector<int> upper_1, upper_2, upper_3, upper_4, upper_5;
      std::vector<int> lower_1, lower_2, lower_3, lower_4, lower_5;

      std::string file_location;

      bool valid_file = false;
      while (!valid_file) {
        std::cout << "\nДля выхода в главное меню напишите exit.\nВведите путь к файлу: ";
        std::cin >> file_location;
        if (file_location == "exit") break;
        /* |проверка файла через good (возвращает bool). Фактически проверяется
         * существует ли файл и можно ли его открыть| */
        std::ifstream file_check(file_location);
        if (!file_check.good()) {
          std::cerr << "Ошибка! Файл не существует или не доступен для чтения.\n";
          file_check.close();
        }
        else {
          /* |проверка файла на соответствие формату .txt| */
          if (file_location.size() < 5 || file_location.substr(file_location.size() - 4) != ".txt")
            std::cerr << "Ошибка! Файл должен иметь расширение .txt\n";
          else {
            /* |проверка файла на пустоту. Если начало файла равно концу, то
             * |файл пуст. Исполняется при помощи eof и peek| */
            file_check.close();
            file_check.open(file_location);
            if (file_check.peek() == std::ifstream::traits_type::eof())
              std::cerr << "Ошибка! Файл пустой.\n";
            else {
              std::string line;
              bool validation_of_all_line = true, is_first_line = true;
              int num_row = 0;
              while (std::getline(file_check, line)) {
                if (is_first_line) {
                  is_first_line = false;
                  continue;
                }
                num_row++;
                int column_count = static_cast<int>(std::count(line.begin(), line.end(), '\t'));
                if (column_count != columns - 1 ) {
                  std::cerr << "Ошибка! В строке должно быть " << columns << " столбцов.\n";
                  validation_of_all_line = false;
                  break;
                }

               
                if (validation_of_all_line == false) break;

                if (line.empty()) {
                  std::cerr << "Ошибка! В файл есть пустые строки.\n";
                  validation_of_all_line = false;
                  break;
                }
                bool valid_symbols = std::all_of(line.begin(), line.end(), [](char c) {
                  return std::isdigit(c) || c == '\t' || c == '-';
                  });
                if (!valid_symbols) {
                  validation_of_all_line = false;
                  break;
                }
                std::stringstream ss(line);
                std::string part;
                bool num_valid = true;

                while (std::getline(ss, part, '\t')) {
                  try {
                    int number = std::stoi(part);
                    number++;
                  }
                  catch (const std::invalid_argument&) {
                    num_valid = false;
                    break;
                  }
                  catch (const std::out_of_range&) {
                    num_valid = false;
                    break;
                  }
                }
                
                

                if (!num_valid) {
                  std::cerr << "Ошибка! В строке числа должы быть числа\n";
                  valid_file = false;
                  break;
                }
              }
              if (num_row != rows) {
                std::cout << "Количество строк не соответвует введенному ранее!\n";
                valid_file = false;
              }
              if (validation_of_all_line) {
                std::cout << "Файл успешно сканирован!\n";
                valid_file = true;
              }
              else
                std::cout << "Файл не прошел проверку, повторите попытку.\n";
            }
          }
        }
      }
      if (file_location == "exit") break;

      std::ifstream file(file_location);
      std::string line;
      std::getline(file, line);

      int row = 0;
      while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string part;
        int col = 0;
        while (std::getline(ss, part, '\t')) {
          if (row < rows && col < columns) {
            matrix[row][col] = std::stoi(part);
            col++;
          }
        }
        row++;
      }

      show_matrix(matrix, rows, columns);

      save_to_file(matrix, rows, columns);


      make_3_vec(matrix, rows, columns, diagonal_1, upper_1, lower_1);
      make_3_vec(matrix, rows, columns, diagonal_2, upper_2, lower_2);
      make_3_vec(matrix, rows, columns, diagonal_3, upper_3, lower_3);
      make_3_vec(matrix, rows, columns, diagonal_4, upper_4, lower_4);
      make_3_vec(matrix, rows, columns, diagonal_5, upper_5, lower_5);


      std::cout << "\nИсходная матрица.\n";
      show_matrix(matrix, rows, columns);


      // bubble_sort
      _bubble.Sort(diagonal_1, num_comparisons, num_permutations, 1);
      _bubble.Sort(upper_1, num_comparisons, num_permutations, 100);
      _bubble.Sort(lower_1, num_comparisons, num_permutations, 1);

      std::cout << "\n\nСортировка пузырьком.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal_1, upper_1, lower_1);


      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);
      std::vector<int> com_and_per;
      com_and_per.push_back(num_comparisons);
      com_and_per.push_back(num_permutations);


      num_comparisons = 0, num_permutations = 0;

      // selection_sort
      _selection.Sort(diagonal_2, num_comparisons, num_permutations, 1);
      _selection.Sort(upper_2, num_comparisons, num_permutations, 100);
      _selection.Sort(lower_2, num_comparisons, num_permutations, 1);

      std::cout << "\n\nСортировка отбором.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal_2, upper_2, lower_2);

      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);
      com_and_per.push_back(num_comparisons);
      com_and_per.push_back(num_permutations);

      num_comparisons = 0, num_permutations = 0;

      // insertion_sort
      _insertion.Sort(diagonal_3, num_comparisons, num_permutations, 1);
      _insertion.Sort(upper_3, num_comparisons, num_permutations, 100);
      _insertion.Sort(lower_3, num_comparisons, num_permutations, 1);


      std::cout << "\n\nСортировка вставкой.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal_3, upper_3, lower_3);

      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);
      com_and_per.push_back(num_comparisons);
      com_and_per.push_back(num_permutations);

      num_comparisons = 0, num_permutations = 0;

      // shell_sort
      _shell.Sort(diagonal_4, num_comparisons, num_permutations, 1);
      _shell.Sort(upper_4, num_comparisons, num_permutations, 100);
      _shell.Sort(lower_4, num_comparisons, num_permutations, 1);

      std::cout << "\n\nСортировка методом Шелла.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal_4, upper_4, lower_4);

      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);
      com_and_per.push_back(num_comparisons);
      com_and_per.push_back(num_permutations);

      num_comparisons = 0, num_permutations = 0;

      // qs
      _quick.Sort(diagonal_5, num_comparisons, num_permutations, 1);
      _quick.Sort(upper_5, num_comparisons, num_permutations, 100);
      _quick.Sort(lower_5, num_comparisons, num_permutations, 1);

      std::cout << "\n\nБыстрая сортировка.\n"
        << "Количество сравнений: " << num_comparisons << std::endl
        << "Количество перестановок: " << num_permutations << std::endl;

      from_vec_to_matrix(matrix, rows, columns, diagonal_5, upper_5, lower_5);
      com_and_per.push_back(num_comparisons);
      com_and_per.push_back(num_permutations);
      std::cout << "\nОтфильтрованная матрица:\n";
      show_matrix(matrix, rows, columns);

      save_to_file(matrix, matrix_copy, rows, columns, com_and_per);

      for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
        delete[] matrix_copy[i];
      }
      delete[] matrix;
      delete[] matrix_copy;
      break;
    }
    case EXIT: return EXIT_SUCCESS;
    }
  }
}


