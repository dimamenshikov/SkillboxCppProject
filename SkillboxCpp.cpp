#include <iostream>

using namespace std;

int main()
{
   setlocale(LC_ALL, "");

   bool correctness = true;
   do
   {
      float result = 1;

      cout << "������� ����� 1: ";
      int number1;
      cin >> number1;

      cout << "������� ���������: ";
      char operation;
      cin >> operation;

      if (operation == '!' && number1 >= 0)
      {
         for (int i = 1; i <= number1; i++)
         {
            result *= i;
         }
         cout << endl << "���������: " << number1 << "! = " << result;
      }
      else if (operation == '!')
      {
         cout << "������ ��������� ��������� ��� �������������� �����";
         cout << endl << "��������� �����������";
         correctness = false;
      }
      else
      {
         cout << "������� ����� 2: ";
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
               cout << "�� ���� ������ ������!";
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
            cout << endl << "���������: " << number1 << " " << operation << " " << number2 << " = " << result;
         }
         else
         {
            cout << endl << "��������� �����������";
         }
      }

      cout << endl << endl << "��� ����������� ������� �" << endl;      
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
