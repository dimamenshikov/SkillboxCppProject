#pragma once

#include <string>
#include <iostream>
#include "CategoryProduct.h"

using namespace std;

class VendingMachine
{
	int quantityCategory = 1, quantityProduct = 0, storage = 100;
	double money = 0;
	CategoryProduct* categories_ptr;
	string** commands_ptr_ptr;

	void (VendingMachine::** functions_ptr_ptr)() = new (void(VendingMachine:: * [9])()){  &VendingMachine::InformationAutomat,
																														&VendingMachine::CommandProduct,
																														&VendingMachine::CommandCategory,
																														&VendingMachine::ProductBuy,
																														&VendingMachine::ProductAdd,
																														&VendingMachine::ProductDelete,
																														&VendingMachine::CategoryAdd,
																														&VendingMachine::CategoryDelete,
																														&VendingMachine::CategoryInformation };
	
	void InformationAutomat();
	void GetMoney();

	void CommandProduct();
	void ProductBuy();
	void ProductAdd();
	void ProductDelete();

	void CommandCategory();
	void CategoryAdd();
	void CategoryDelete();
	void CategoryInformation();

	bool FindCommand(string, int, int&) const;
	bool StringToDouble(const string&, double*);
	bool StringToInt(const string&, int*);

public:
	void Launch();
	VendingMachine() = default;
	VendingMachine(int quantityCategory = 0, int storage = 100, double money = 0);
	~VendingMachine();
};