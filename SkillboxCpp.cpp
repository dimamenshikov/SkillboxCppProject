#include <iostream>

using namespace std;

int main()
{
   setlocale(LC_ALL, "");

   bool correctness = true;
   do
   {
      float result = 1;

      cout << "Введите число 1: ";
      int number1;
      cin >> number1;

      cout << "Введите выражение: ";
      char operation;
      cin >> operation;

      if (operation == '!' && number1 >= 0)
      {
         for (int i = 1; i <= number1; i++)
         {
            result *= i;
         }
         cout << endl << "Результат: " << number1 << "! = " << result;
      }
      else if (operation == '!')
      {
         cout << "Нельзя посчитать факториал для отрицательного числа";
         cout << endl << "Выражение некорректно";
         correctness = false;
      }
      else
      {
         cout << "Введите число 2: ";
         int number2;
         cin >> number2;         

         switch (operation)
         {
         case '+':
            result = number1 + number2;
            break;
         case '-':
            result = number1 - number2;
            break;
         case '*':
            result = number1 * number2;
            break;
         case '/':
            if (number2)
            {
               result = (float)number1 / number2;
            }
            else
            {
               cout << "На ноль делить нельзя!";
               correctness = false;
            }
            break;
         case '^':          
            for (int i = 0; i < (number2 > 0 ? number2 : -number2); i++)
            {
               result *= number1;
            }
            result = number2 > 0 ? result : 1 / result;
            break;
         default:
            correctness = false;
            break;
         }
         if (correctness)
         {
            cout << endl << "Результат: " << number1 << " " << operation << " " << number2 << " = " << result;
         }
         else
         {
            cout << endl << "Выражение некорректно";
         }
      }

      cout << endl << endl << "Для продолжения введите с" << endl;      
      char command = ' ';
      cin >> command;
      cout << endl;

      if (command == 'c' || command == 'C')
      {
         correctness = true;
      }
      else 
      {
         break;
      }  
   } while (correctness);

   return 0;
}
