#include <iostream>
#include "VendingMachine.h"
#include <Windows.h>

using namespace std;

int main()
{
   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);

   cout << "Торговый автомат запущен\n";

   VendingMachine* automat_ptr = new VendingMachine(3, 10, 500);
   automat_ptr->Launch();

   delete automat_ptr;

   return 0;
}
