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
		cout << "\n��������: " << name << "\n";
		cout << "����������: " << quantityProduct << "\n";
		cout << "���������: " << cost << "\n";
		cout << "���: " << weight << "\n";
		cout << "�����������: " << manufacturer << "\n";
	}
	else
	{
		cout << "\t" << number << "\t" << name << "\t\t\t" << quantityProduct << "\t\t\t" << cost;
	}
}