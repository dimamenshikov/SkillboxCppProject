#include "VendingMachine.h"

VendingMachine::VendingMachine(int quantityCategory, int storage, double money)
{
	commands_ptr_ptr = new string * [3];
	commands_ptr_ptr[0] = new string[3]{ "автомат", "продукт", "категория" };
	commands_ptr_ptr[1] = new string[3]{ "купить", "добавить", "убрать" };
	commands_ptr_ptr[2] = new string[3]{ "добавить", "удалить", "информация" };

	this->quantityCategory = quantityCategory > 0 ? quantityCategory : 0;
	this->storage = storage > 0 ? storage : 0;
	this->money = money > 0 ? money : 0;
	categories_ptr = new CategoryProduct[quantityCategory];
	for (int i = 0; i < quantityCategory; ++i)
	{
		quantityProduct += categories_ptr[i].quantityProduct;
		if (quantityProduct > storage)
		{
			categories_ptr[i].quantityProduct -= quantityProduct - storage;
			quantityProduct = storage;
		}
		categories_ptr[i].number = i + 1;
	}
}

VendingMachine::~VendingMachine()
{
	for (int i = 0; i < 3; i++)
	{
		delete[] commands_ptr_ptr[i];
	}
	delete[] commands_ptr_ptr;
	delete[] categories_ptr;
	delete[] functions_ptr_ptr;
}

void VendingMachine::Launch()
{
Command:
	cout << "\nВведите команду: автомат/продукт/категория/снять деньги/выход\n";
	string command;
	getline(cin, command);
	if (command == "выход")
	{
		return;
	}
	if (command == "снять деньги")
	{
		GetMoney();
		goto Command;
	}
	int indexCommand;
	if (FindCommand(command, 0, indexCommand))
	{
		(this->*functions_ptr_ptr[indexCommand])();
	}
	else
	{
		cout << command << " - Нет такой команды\n";
	}
	goto Command;
}

void VendingMachine::InformationAutomat()
{
	cout << "\n\t№\t" << "Развидность\t\t" << "Количество\t\t" << "Стоимость\t\n";
	cout << "\t-----------------------------------------------------------------\n";
	for (int i = 0; i < quantityCategory; ++i)
	{
		categories_ptr[i].Information();
		cout << "\n";
	}
	cout << "\nКоличество денег в автомате\t\t" << money;
	cout << "\nКоличество продуктов в автомате\t\t" << quantityProduct;
	cout << "\nВсего мест в автомате\t\t\t" << storage;
	cout << "\nКоличество пустых мест в автомате\t" << storage - quantityProduct << "\n\n";
}

void VendingMachine::GetMoney()
{
	cout << "\n" << money << " снято\n";
	money = 0;
}

void VendingMachine::CommandProduct()
{
	cout << "\nВведите команду: купить/добавить/убрать\n";
	string command;
	int indexCommand;
	getline(cin, command);
	if (!FindCommand(command, 1, indexCommand))
	{
		cout << "\nНекорректный ввод\n";
		return;
	}
	(this->*functions_ptr_ptr[indexCommand])();
}

void VendingMachine::CommandCategory()
{
	cout << "\nВведите команду: добавить/удалить/информация\n";
	string command;
	int indexCommand;
	getline(cin, command);
	if (!FindCommand(command, 2, indexCommand))
	{
		cout << "\nНекорректный ввод\n";
		return;
	}
	(this->*functions_ptr_ptr[indexCommand])();
}

void VendingMachine::ProductBuy()
{	
	cout << "\nВведите номер категории ";
	string input;
	getline(cin, input);
	int number;
	if (!StringToInt(input, &number))
	{
		cout << "\nНекорректный ввод\n";
		return;
	}
	--number;
	if (number < 0 || number >= quantityCategory)
	{
		cout << input << " - Нет такой категории\n";
		return;
	}
	if (categories_ptr[number].quantityProduct <= 0)
	{
		cout << "Продукт кончился\n";
		return;
	}
	cout << "\nВведите количество продуктов ";
	getline(cin, input);
	int quantityProduct;
	if (!StringToInt(input, &quantityProduct))
	{
		cout << "\nНекорректный ввод\n";
		return;
	}
	if (categories_ptr[number].quantityProduct < quantityProduct || quantityProduct <= 0)
	{
		cout << "\nВ автомате нет столько продуктов такой категории\n";
		return;
	}
	cout << "\nИтого к оплате " << quantityProduct * categories_ptr[number].cost;
	cout << "\n\nВведите деньги ";
	getline(cin, input);
	double money;
	if (!StringToDouble(input, &money))
	{
		cout << "\nНекорректный ввод\n";
		return;
	}
	if (money >= categories_ptr[number].cost)
	{
		cout << "\nВы приобрели " << categories_ptr[number].name << "\nВаша сдача " << money - categories_ptr[number].cost * quantityProduct << "\n";
		categories_ptr[number].quantityProduct -= quantityProduct;
		this->quantityProduct -= quantityProduct;
		this->money += categories_ptr[number].cost * quantityProduct;
	}
	else 
	{
		cout << "\nНедостаточно денег\n";
	}
}

void VendingMachine::ProductAdd()
{
	cout << "\nВведите номер категории ";
	string input;
	getline(cin, input);
	int number;
	if (!StringToInt(input, &number))
	{
		cout << "\nНекорректный ввод\n";
		return;
	}
	--number;
	if (number < 0 || number >= quantityCategory)
	{
		cout << input << " - Нет такой категории\n";
		return;
	}
	cout << "\nВведите количество продуктов ";
	getline(cin, input);
	int quantityProduct;
	if (!StringToInt(input, &quantityProduct))
	{
		cout << "\nНекорректный ввод\n";
		return;
	}
	if (quantityProduct <= 0)
	{
		cout << "\nВы ввели не натуральное число\n";
		return;
	}
	if (quantityProduct + this->quantityProduct > storage)
	{
		cout << "\nПереполнение автомата, автомат будет заполнен полностью\n";
		quantityProduct = storage - this->quantityProduct;
	}
	categories_ptr[number].quantityProduct += quantityProduct;
	this->quantityProduct += quantityProduct;
	cout << "\nПродукты добавлены\n";
}

void VendingMachine::ProductDelete()
{
	cout << "\nВведите номер категории ";
	string command;
	getline(cin, command);
	int number;
	if (!StringToInt(command, &number))
	{
		cout << "\nНекорректный ввод\n";
		return;
	}
	--number;
	if (number < 0 || number >= quantityCategory)
	{
		cout << command << " - Нет такой категории\n";
		return;
	}
	cout << "\nВведите количество продуктов ";
	getline(cin, command);
	int quantityProduct;
	if (!StringToInt(command, &quantityProduct))
	{
		cout << "\nНекорректный ввод\n";
		return;
	}
	if (quantityProduct <= 0)
	{
		cout << "\nВы ввели не натуральное число\n";
		return;
	}
	if (quantityProduct > categories_ptr[number].quantityProduct)
	{
		quantityProduct = categories_ptr[number].quantityProduct;
		cout << "\nВаше число больше числа продуктов, будут убраны все продукты\n";

	}
	categories_ptr[number].quantityProduct -= quantityProduct;
	this->quantityProduct -= quantityProduct;
	cout << "\nПродукты убраны\n";
}

void VendingMachine::CategoryAdd()
{
	CategoryProduct* newCategory_ptr = new CategoryProduct;
	cout << "\nВведите данные категории";	
	cout << "\nВведите имя категории ";	
	string input;
	getline(cin, newCategory_ptr->name);
	cout << "\nВведите производителя ";	
	getline(cin, newCategory_ptr->manufacturer);
	cout << "\nВведите количество продуктов ";
	getline(cin, input);
	int number;
	if (!StringToInt(input, &number))
	{
		cout << "\nНекорретный ввод\n";
		delete newCategory_ptr;
		return;
	}
	if (number < 0)
	{
		cout << "\nВы ввели не натуральное число\n";
		delete newCategory_ptr;
		return;
	}
	if (number + quantityProduct > storage)
	{
		cout << "\nПереполнение автомата, автомат будет заполнен полностью\n";
		number = storage - quantityProduct;
	}
	quantityProduct += number;
	newCategory_ptr->quantityProduct = number;
	cout << "\nВведите стоимость продукта ";
	getline(cin, input);
	double numberDouble;
	if (!StringToDouble(input, &numberDouble))
	{
		cout << "\nНекорретный ввод\n";
		delete newCategory_ptr;
		return;
	}
	if (numberDouble < 0)
	{
		cout << "\nВы ввели не положительное число\n";
		delete newCategory_ptr;
		return;
	}
	newCategory_ptr->cost = numberDouble;
	cout << "\nВведите вес продукта ";
	getline(cin, input);
	if (!StringToDouble(input, &numberDouble))
	{
		cout << "\nНекорретный ввод\n";
		delete newCategory_ptr;
		return;
	}
	if (numberDouble < 0)
	{
		cout << "\nВы ввели не положительное число\n";
		delete newCategory_ptr;
		return;
	}
	newCategory_ptr->weight = numberDouble;
	++quantityCategory;
	newCategory_ptr->number = quantityCategory;

	CategoryProduct* temp_ptr = new CategoryProduct[quantityCategory];
	temp_ptr[quantityCategory - 1] = *newCategory_ptr;
	for (int i = 0; i < quantityCategory - 1; ++i)
	{
		temp_ptr[i] = categories_ptr[i];
	}

	delete[] categories_ptr;
	categories_ptr = temp_ptr;
	delete newCategory_ptr;
	cout << "\nКатегория добавлена\n";
}

void VendingMachine::CategoryDelete()
{
	if (quantityCategory > 0)
	{
		cout << "\nВведите номер категории ";
		string input;
		getline(cin, input);
		int number;
		if (!StringToInt(input, &number))
		{
			cout << "\nНекорректный ввод\n";
			return;
		}
		--number;
		if (number < 0 || number >= quantityCategory)
		{
			cout << input << " - Нет такой категории\n";
			return;
		}
		--quantityCategory;
		this->quantityProduct -= categories_ptr[number].quantityProduct;
		CategoryProduct* temp_ptr = new CategoryProduct[quantityCategory];
		for (int i = 0; i < number; ++i)
		{
			temp_ptr[i] = categories_ptr[i];
		}
		for (int i = number; i < quantityCategory; ++i)
		{
			temp_ptr[i] = categories_ptr[i + 1];
			temp_ptr[i].number = categories_ptr[i + 1].number - 1;
		}
		delete[] categories_ptr;
		categories_ptr = temp_ptr;
		cout << "\nКатегория удалена\n";
	}
	else
	{
		cout << "\nКатегорий нет\n";
	}
}

void VendingMachine::CategoryInformation()
{
	cout << "\nВведите номер категории ";
	string input;
	getline(cin, input);
	int number;
	if (!StringToInt(input, &number))
	{
		cout << "\nНекорректный ввод\n";
		return;
	}
	--number;
	if (number < 0 || number >= quantityCategory)
	{
		cout << input << " - Нет такой категории\n";
		return;
	}
	else
	{
		categories_ptr[number].Information(true);
	}
}

bool VendingMachine::FindCommand(string command, int indexCommand, int& number) const
{
	for (int i = 0; i < 3; ++i)
	{
		if (commands_ptr_ptr[indexCommand][i] == command)
		{
			number = i + 3 * indexCommand;
			return true;
		}
	}
	return false;
}

bool VendingMachine::StringToDouble(const string& s, double* result)
{
	*result = 0;
	int minus;
	switch(s.length())
	{
	case 0:
		return false;
	case 1:
		if (s[0] == '.' || s[0] == '-')
		{
			return false;
		}
		break;
	case 2:
		if (s[0] == '.' || s[1] == '.' || s[0] == '0')
		{
			return false;
		}
		break;
	default:
		minus = (s[0] == '-' ? 1 : 0);
		if ((s[minus] == '0' && s[minus + 1] != '.') || s[minus] == '.')
		{
			return false;
		}
		break;
	}
	minus = (s[0] == '-' ? 1 : 0);
	bool point = false;
	for (int i = minus, j = 10; i < s.length(); ++i)
	{
		if ((s[i] < 48 && s[i] != 46) || s[i] > 57)
		{
			*result = 0;
			return false;
		}
		else
		{
			if (s[i] != 46)
			{
				if (point)
				{
					*result += (double)(s[i] - 48) / j;
					j *= 10;
				}
				else
				{
					*result = *result * 10 + (s[i] - 48);
				}
			}
			else
			{
				if (point)
				{
					*result = 0;
					return false;
				}
				point = true;
			}
		}
	}
	*result = (minus == 1 ? -*result : *result);
	return true;
}

bool VendingMachine::StringToInt(const string& s, int* result)
{
	*result = 0;
	switch(s.length())
	{
	case 0:
		return false;
	case 1:
		if (s[0] == '-')
		{
			return false;
		}
		break;
	case 2:
		if (s[0] == '0')
		{
			return false;
		}
		break;
	default:
		if (s[0] == '0' || (s[0] == '-' && s[1] == '0'))
		{
			return false;
		}
		break;
	}
	bool minus = s[0] == '-';
	for (int i = minus; i < s.length(); ++i)
	{
		if (s[i] < 48 || s[i] > 57)
		{
			*result = 0;
			return false;
		}
		else
		{
			*result = *result * 10 + (s[i] - 48);
		}
	}
	*result = minus ? -*result : *result;
	return true;
}