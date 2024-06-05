#include "3_utilities.h"


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


void make_3_vec(int** matrix, int rows, int columns, std::vector<int>& diagonal,
  std::vector<int>& upper, std::vector<int>& lower)
{
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; ++j)
      if (i == j) { diagonal.push_back(matrix[i][j]); }
      else if (i < j) { upper.push_back(matrix[i][j]); }
      else { lower.push_back(matrix[i][j]); }

}

void from_vec_to_matrix(int**& matrix, int rows, int columns, std::vector<int>& diagonal,
  std::vector<int>& upper, std::vector<int>& lower)
{
  int k1 = 0, k2 = 0, k3 = 0;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++)
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

void show_matrix(int** matrix, int rows, int columns)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			std::cout << matrix[i][j] << " \t";
		std::cout << "\n";
	}
}

void swap_matrix(int** original, int** copy, int rows, int cols) {
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j)
      original[i][j] = copy[i][j];
}

void save_to_file(int **matrix, int rows, int cols)
{
	InputCheck _input;
	const int save = 1, not_save = 0;
	int save_to_file = 0;

	std::cout << "\n\nХотите сохранить список в файл? (0 - Нет, "
		"1 - Да): ";

	save_to_file = _input.get_int();
	while (save_to_file != not_save && save_to_file != save) {
		std::cout << "Сделайте выбор (0 - Не сохранять в файл, 1 - Сохранить в "
			"файл): ";
		save_to_file = _input.get_int();
	}

	if (save_to_file == 1) {

		std::vector<std::string> reserved_names = { "CON.", "PRN.", "AUX.", "NUL.",
																							"COM1.", "COM2.", "COM3.", "COM4.", "COM5", "COM6", "COM7", "COM8.", "COM9.",
																							"LPT1.", "LPT2.", "LPT3.", "LPT4.", "LPT5.", "LPT6.", "LPT7.", "LPT8.", "LPT9.",
																							"CONIN$.", "CONOUT$.", "PRINTER$.", "CLOCK$.", "NUL$." };

		for (;;) {
			std::string file_name;
			std::cout << "Введите имя файла или 'exit' для выхода: ";
			std::cin >> file_name;

			if (file_name == "exit")
				break;

			std::string file_name_copy = file_name;
			size_t found = file_name_copy.find_last_of('\\');

			if (found != std::string::npos)
				file_name_copy = file_name_copy.substr(found + 1);


			bool err_sym = false;
			for (char c : file_name_copy)
				if (c == ':' || c == '/' || c == ',' || c == '*' || c == '"' || c == '<' || c == '>' || c == '|') {
					err_sym = true;
					break;
				}

			if (err_sym) {
				std::cout << "Имя файла содержит недопустимые символы!\n";
				break;
			}
			std::transform(file_name_copy.begin(), file_name_copy.end(), file_name_copy.begin(), ::toupper);

			bool is_reserved = false;

			if (file_name_copy.size() >= 5) {
				for (const std::string& reserved : reserved_names) {
					size_t search_length = std::min(file_name_copy.size(), reserved.size());
					size_t pos = file_name_copy.substr(0, search_length).find(reserved, 0);

					if (pos != std::string::npos) {
						is_reserved = true;
						break;
					}
				}
			}
			else {
				is_reserved = true;
			}



			if (is_reserved) {
				std::cout << "Введено зарезервированное имя для OC Windows 10 или расширение файла не .txt" << std::endl;
				continue;
			}

			if (file_name_copy.substr(file_name_copy.size() - 4) != ".TXT") {
				std::cout << "Должен быть формат .txt, повторите попытку!" << std::endl;
				continue;
			}



			if (std::filesystem::exists(file_name)) {
				std::cout << "\nФайл с именем '" << file_name << "' существует.\n";
				std::cout << "Выберите один из пунктов.\n0)Сохранить данные в этот файл(данные будут стерты)\n1)Выбрать другой файл для сохранения\n";
				save_to_file = _input.get_int();
				while (save_to_file != not_save && save_to_file != save) {
					std::cout << "Сделайте выбор (0 - Сохранить данные в этот файл(данные будут стерты), 1 - Сохранить в "
						"другой файл): ";
					save_to_file = _input.get_int();
				}
				if (save_to_file == 0) {
					std::ofstream output_file(file_name);
					if (output_file.is_open()) {
						
						output_file << "Исходная матрица\n";
						for (int i = 0; i < rows; i++) {
							for (int j = 0; j < cols - 1; j++)
								output_file << matrix[i][j] << "\t";
							output_file << matrix[i][cols - 1] << "\n";
						}
						
						std::cout << "Данные успешно сохранены в файл: " << file_name << "\n";
						break;
					}
					else {
						std::cout << "Файл не доступен для записи, повторите попытку!\n";
						continue;
					}
				}
				else continue;
			}
			else {
				std::ofstream output_file(file_name);
				if (output_file.is_open()) {
					output_file << "Исходная матрица\n";
					for (int i = 0; i < rows; i++) {
						for (int j = 0; j < cols - 1; j++)
							output_file << matrix[i][j] << "\t";
						output_file << matrix[i][cols - 1] << "\n";
					}
					std::cout << "Данные успешно сохранены в файл: " << file_name << "\n";
					break;
				}
				else {
					std::cout << "Файл не доступен для записи, повторите попытку!\n";
					continue;
				}
			}
		}
	}
	else std::cout << "Данные не будут сохранены в файл";
}

void save_to_file(int** matrix, int **matrix_copy, int rows, int cols, std::vector<int> com_and_per)
{
	InputCheck _input;
	const int save = 1, not_save = 0;
	int save_to_file = 0;

	std::cout << "\n\nХотите сохранить список в файл? (0 - Нет, "
		"1 - Да): ";

	save_to_file = _input.get_int();
	while (save_to_file != not_save && save_to_file != save) {
		std::cout << "Сделайте выбор (0 - Не сохранять в файл, 1 - Сохранить в "
			"файл): ";
		save_to_file = _input.get_int();
	}

	if (save_to_file == 1) {

		std::vector<std::string> reserved_names = { "CON.", "PRN.", "AUX.", "NUL.",
																							"COM1.", "COM2.", "COM3.", "COM4.", "COM5", "COM6", "COM7", "COM8.", "COM9.",
																							"LPT1.", "LPT2.", "LPT3.", "LPT4.", "LPT5.", "LPT6.", "LPT7.", "LPT8.", "LPT9.",
																							"CONIN$.", "CONOUT$.", "PRINTER$.", "CLOCK$.", "NUL$." };

		for (;;) {
			std::string file_name;
			std::cout << "Введите имя файла или 'exit' для выхода: ";
			std::cin >> file_name;

			if (file_name == "exit")
				break;

			std::string file_name_copy = file_name;
			size_t found = file_name_copy.find_last_of('\\');

			if (found != std::string::npos)
				file_name_copy = file_name_copy.substr(found + 1);


			bool err_sym = false;
			for (char c : file_name_copy)
				if (c == ':' || c == '/' || c == ',' || c == '*' || c == '"' || c == '<' || c == '>' || c == '|') {
					err_sym = true;
					break;
				}

			if (err_sym) {
				std::cout << "Имя файла содержит недопустимые символы!\n";
				break;
			}
			std::transform(file_name_copy.begin(), file_name_copy.end(), file_name_copy.begin(), ::toupper);

			bool is_reserved = false;

			if (file_name_copy.size() >= 5) {
				for (const std::string& reserved : reserved_names) {
					size_t search_length = std::min(file_name_copy.size(), reserved.size());
					size_t pos = file_name_copy.substr(0, search_length).find(reserved, 0);

					if (pos != std::string::npos) {
						is_reserved = true;
						break;
					}
				}
			}
			else {
				is_reserved = true;
			}



			if (is_reserved) {
				std::cout << "Введено зарезервированное имя для OC Windows 10 или расширение файла не .txt" << std::endl;
				continue;
			}

			if (file_name_copy.substr(file_name_copy.size() - 4) != ".TXT") {
				std::cout << "Должен быть формат .txt, повторите попытку!" << std::endl;
				continue;
			}



			if (std::filesystem::exists(file_name)) {
				std::cout << "\nФайл с именем '" << file_name << "' существует.\n";
				std::cout << "Выберите один из пунктов.\n0)Сохранить данные в этот файл(данные будут стерты)\n1)Выбрать другой файл для сохранения\n";
				save_to_file = _input.get_int();
				while (save_to_file != not_save && save_to_file != save) {
					std::cout << "Сделайте выбор (0 - Сохранить данные в этот файл(данные будут стерты), 1 - Сохранить в "
						"другой файл): ";
					save_to_file = _input.get_int();
				}
				if (save_to_file == 0) {
					std::ofstream output_file(file_name);
					if (output_file.is_open()) {
						output_file << "Исходная матрица\n";
						for (int i = 0; i < rows; i++) {
							for (int j = 0; j < cols; j++)
								output_file << matrix_copy[i][j] << "\t";
							output_file << "\n";
						}

						output_file << "Отсортированная матрица\n";
						for (int i = 0; i < rows; i++) {
							for (int j = 0; j < cols; j++)
								output_file << matrix[i][j] << "\t";
							output_file << "\n";
						}
						output_file << "\n\nСравнительная таблица эффективности методов сортировки\n"
							"                        Число сравнений Число перестановок\n"
							"Пузырьковая сортировка:\t" << com_and_per[0] << "\t \t" << com_and_per[1] << "\n"
							"          Метод отбора:\t" << com_and_per[2] << "\t \t" << com_and_per[3] << "\n"
							"         Метод вставки:\t" << com_and_per[4] << "\t \t" << com_and_per[5] << "\n"
							"           Метод Шелла:\t" << com_and_per[6] << "\t \t" << com_and_per[7] << "\n"
							"    Быстрая сортировка:\t" << com_and_per[8] << "\t \t" << com_and_per[9];

						std::cout << "Данные успешно сохранены в файл: " << file_name << "\n";
						break;
					}
					else {
						std::cout << "Файл не доступен для записи, повторите попытку!\n";
						continue;
					}
				}
				else continue;
			}
			else {
				std::ofstream output_file(file_name);
				if (output_file.is_open()) {
					output_file << "Исходная матрица\n";
					for (int i = 0; i < rows; i++) {
						for (int j = 0; j < cols; j++)
							output_file << matrix_copy[i][j] << "\t";
						output_file << "\n";
					}

					output_file << "Отсортированная матрица\n";
					for (int i = 0; i < rows; i++) {
						for (int j = 0; j < cols; j++)
							output_file << matrix[i][j] << "\t";
						output_file << "\n";
					}
					output_file << "\n\nСравнительная таблица эффективности методов сортировки\n"
						"                        Число сравнений Число перестановок\n"
						"Пузырьковая сортировка:\t" << com_and_per[0] << "\t \t" << com_and_per[1] << "\n"
						"          Метод отбора:\t" << com_and_per[2] << "\t \t" << com_and_per[3] << "\n"
						"         Метод вставки:\t" << com_and_per[4] << "\t \t" << com_and_per[5] << "\n"
						"           Метод Шелла:\t" << com_and_per[6] << "\t \t" << com_and_per[7] << "\n"
						"    Быстрая сортировка:\t" << com_and_per[8] << "\t \t" << com_and_per[9];


					std::cout << "Данные успешно сохранены в файл: " << file_name << "\n";
					break;
				}
				else {
					std::cout << "Файл не доступен для записи, повторите попытку!\n";
					continue;
				}
			}
		}
	}
	else std::cout << "Данные не будут сохранены в файл";
}