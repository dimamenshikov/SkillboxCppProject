#include "CategoryProduct.h"

using namespace std;

CategoryProduct::CategoryProduct(const CategoryProduct& other)
{
	this->name = other.name;
	this->manufacturer = other.manufacturer;
	this->cost = other.cost;
	this->weight = other.weight;
	this->quantityProduct = other.quantityProduct;
	this->number = other.number;
}

CategoryProduct& CategoryProduct::operator=(const CategoryProduct& other)
{
	this->name = other.name;
	this->manufacturer = other.manufacturer;
	this->cost = other.cost;
	this->weight = other.weight;
	this->quantityProduct = other.quantityProduct;
	this->number = other.number;
	return *this;
}

void CategoryProduct::Information(bool full) const
{
	if (full)
	{
		cout << "\nНазвание: " << name << "\n";
		cout << "Количество: " << quantityProduct << "\n";
		cout << "Стоимость: " << cost << "\n";
		cout << "Вес: " << weight << "\n";
		cout << "Произведено: " << manufacturer << "\n";
	}
	else
	{
		cout << "\t" << number << "\t" << name << "\t\t\t" << quantityProduct << "\t\t\t" << cost;
	}
}