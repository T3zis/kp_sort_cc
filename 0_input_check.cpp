/*______HEADER-FILES______*/
#include "0_input_check.h"
/*________________________*/


/*________________get-int________________*/
int InputCheck::get_int(void)
{
  int         res{0};
  std::string input_str;
  bool        correctness{false};

  while (!correctness) {
    std::cin  >> input_str;
    try {
      size_t pos_symbol;
      res = std::stoi(input_str, &pos_symbol);
      if (pos_symbol != input_str.size())
        throw std::invalid_argument("Ошибка! Введенное значение не является целым числом.");     
      correctness ^= true;
    }
    catch (const std::invalid_argument) { std::cout << "Повторите попытку.\n";                      }
    catch (const std::out_of_range)     { std::cout << "Ошибка! Введенное значение находится вне "
                                                       "диапазона целыхчисел. Повторите попытку.\n";}
    
    /* |сброс состояния потока ввода + сбрасывает любые флаги ошибок| */
    std::cin.clear();
    /* |игнорирование всех символов во входном буфере до \n| */
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    
  }
  return res;
}
/*_______________________________________*/


/*________________get-double________________*/
double InputCheck::get_double(void)
{
  double      res{0};
  std::string input_str;
  bool        correctness{false};

  while (!correctness) {
    std::cout << "Введите вещественное число: ";
    std::cin  >> input_str;
    try {
      size_t pos_symbol;
      res = std::stod(input_str, &pos_symbol);
      if (pos_symbol != input_str.size())
        throw std::invalid_argument("Ошибка! Введенное значение не является вещественным числом.\n");
      correctness ^= true;
    }
    catch (const std::invalid_argument) { std::cout << "Повторите попытку!\n";                     }
    catch (const std::out_of_range)     { std::cout << "Число находится вне диапазона вещественных"
                                                       "чисел, повторите попытку!\n";              }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return res;
}
/*___________________________________________*/
