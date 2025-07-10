#pragma once

#include <iostream>

using namespace std;

class CategoryProduct
{
public:
	int quantityProduct = 1, number = 0;
	double cost = 100, weight = 0;
	string name = "Твикс", manufacturer = "Россия";

	CategoryProduct& operator=(const CategoryProduct&);

	void Information(bool full = false) const;

	CategoryProduct() = default;
	CategoryProduct(const CategoryProduct&);
	~CategoryProduct() = default;
};