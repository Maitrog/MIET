#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Bank.h"

void ShowTableHeader();
Bank* SortByDeposit(Bank*);

int main()
{
	setlocale(0, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::fstream file("base.txt", std::ios::app);
	file.close();

	std::ifstream fin("base.txt");
	Bank* bank_base = new Bank[0];
	Bank* tmp;
	std::string _name;
	std::string _lastname;
	std::string _secondName;
	int _number;
	double _deposit;

	if (!fin)
	{
		std::cout << "Ошибка открытия файла.\n";
		return -1;
	}

	while (fin >> _number)
	{
		fin >> _name;
		fin >> _lastname;
		fin >> _secondName;
		fin >> _deposit;

		tmp = new Bank[Bank::count + 1];
		for (int i = 0; i < (Bank::count - 1) / 2; i++)
		{
			tmp[i] = bank_base[i];
		}
		delete[] bank_base;
		bank_base = tmp;
		bank_base[Bank::count - 2] = Bank(Fio(_name, _lastname, _secondName), _number, _deposit);
	}
	fin.close();

	std::ofstream fout("base.txt");
	int k;
	for (;;)
	{
		std::cout << "1.Добавить банковский счёт." << std::endl;
		std::cout << "2.Вывести таблицу на экран." << std::endl;;
		std::cout << "3.Сортировать счета по уменьшению суммы депозита." << std::endl;
		std::cout << "4.Поиск счёта по номеру." << std::endl;
		std::cout << "5.Добавить сумму на счёт." << std::endl;
		std::cout << "6.Выход." << std::endl;
		while (true)
		{
			std::cout << "Введите команду: ";
			std::cin >> k;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(32768, '\n');
				std::cout << "Ошибка ввода!\n";
			}
			else
				break;
		}
		switch (k)
		{
		case 1:
			tmp = new Bank[Bank::count + 1];
			for (int i = 0; i < (Bank::count - 1) / 2; ++i)
			{
				tmp[i] = bank_base[i];
			}
			delete[] bank_base;
			bank_base = tmp;
			std::cin >> bank_base[Bank::count - 1];
			break;
		case 2:
			ShowTableHeader();
			for (size_t i = 0; i < Bank::count; ++i)
			{
				std::cout << bank_base[i] << std::endl;
			}
			break;
		case 3:
			bank_base = SortByDeposit(bank_base);
			ShowTableHeader();
			for (size_t i = 0; i < Bank::count; ++i)
			{
				std::cout << bank_base[i] << std::endl;
			}
			break;
		case 4:
			std::cout << "Введите номер счёта: ";
			std::cin >> _number;
			for (int i = 0; i < Bank::count; i++)
			{
				if (bank_base[i].get_number() == _number)
				{
					ShowTableHeader();
					std::cout << bank_base[i] << std::endl;
					break;
				}
			}
			break;
		case 5:
			ShowTableHeader();
			for (size_t i = 0; i < Bank::count; ++i)
			{
				std::cout << bank_base[i] << std::endl;
			}

			std::cout << "Введите номер счёта, к которому хотите добавить сумму: ";
			std::cin >> _number;
			std::cout << "Введите сумму, которую хотитк добавить: ";
			std::cin >> _deposit;
			for (int i = 0; i < Bank::count; i++)
			{
				if (bank_base[i].get_number() == _number)
				{
					bank_base[i] = bank_base[i] + _deposit;
					break;
				}
			}
			break;
		case 6:
			for (size_t i = 0; i < Bank::count; ++i)
			{
				fout << bank_base[i];
			}
			fout.close();
			delete[] bank_base;
			return 0;
			break;
		default:
			std::cout << "Такой команды не существует.\n";
			break;
		}
	}
	return 0;
}

void ShowTableHeader()
{
	std::cout << std::endl;
	std::cout.setf(std::ios::left);
	std::cout.width(15);
	std::cout << "Номер счёта";
	std::cout.width(30);
	std::cout << "Фамилия";
	std::cout.width(30);
	std::cout << "Имя";
	std::cout.width(30);
	std::cout << "Отчество";
	std::cout.width(10);
	std::cout << "Депозит" << std::endl;
	std::cout << std::string(115, '-') << std::endl;
}

Bank* SortByDeposit(Bank* bank_base)
{
	for (int step = Bank::count / 2; step > 0; step /= 2)
		for (int i = step; i < Bank::count; i++)
			for (int j = i - step; j >= 0 && bank_base[j].get_deposit() < bank_base[j + step].get_deposit(); j -= step)
				std::swap(bank_base[j], bank_base[j + step]);
	return bank_base;
}