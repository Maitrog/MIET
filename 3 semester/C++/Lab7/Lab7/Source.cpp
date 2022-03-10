//Тюльников Михаил ПИН-22 Вариант 24
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Ticket.h"
#include "DeparturStationComparer.h"
#include "ArrivalStaitionFind.h"
#include "FioFind.h"

void show_table();
Ticket* sortByDepartureStation(Ticket*);

int main()
{
	setlocale(0, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::fstream file("base.txt", std::ios::app);
	file.close();

	std::ifstream fin("base.txt");
	std::vector<Ticket> ticket_base;
	std::vector<Ticket>::iterator it;

	std::string _name;
	std::string _lastName;
	std::string _secondName;
	std::string _arrivalStation;
	std::string _departureStation;
	int count = 0;
	double _cost;

	if (!fin)
	{
		std::cout << "Ошибка открытия файла.\n";
		return -1;
	}

	while (fin >> _name)
	{
		fin >> _lastName;
		fin >> _secondName;
		fin >> _departureStation;
		fin >> _arrivalStation;
		fin >> _cost;

		ticket_base.push_back(Ticket(Fio(_name, _lastName, _secondName), _departureStation, _arrivalStation, _cost));
	}
	fin.close();

	std::ofstream fout("base.txt");
	int k;
	for (;;)
	{
		std::cout << "1.Добавить билет." << std::endl;
		std::cout << "2.Вывести таблицу на экран." << std::endl;;
		std::cout << "3.Сортировать билеты по пункту отправления." << std::endl;
		std::cout << "4.Поиск билетов по пункту прибытия." << std::endl;
		std::cout << "5.Удалить последний добавленнйы билет" << std::endl;
		std::cout << "6.Найти билет по ФИО пасажира" << std::endl;
		std::cout << "7.Выход." << std::endl;
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
			ticket_base.push_back(Ticket());
			std::cin >> ticket_base[ticket_base.size() - 1];
			break;
		case 2:
			show_table();
			for (auto i : ticket_base)
			{
				std::cout << i;
			}
			break;
		case 3:
			std::sort(ticket_base.begin(), ticket_base.end(), DeparturStationComparer());
			show_table();
			for (auto i : ticket_base)
			{
				std::cout << i;
			}
			break;
		case 4:
			std::cout << "Введите пункт назначения: ";
			std::cin >> _arrivalStation;
			count = 0;
			it = ticket_base.begin();
			while (it != ticket_base.end())
			{
				it = std::find_if(it, ticket_base.end(), ArrivalStaitionFind(_arrivalStation));
				if (it == ticket_base.end() && count == 0)
				{
					std::cout << "Таких билетов не найдено" << std::endl << std::endl;
					break;
				}
				if (count == 0 && it != ticket_base.end())
					show_table();
				count++;
				std::cout << *it;
				if (it != ticket_base.end())
					it++;
			}
			break;
		case 5:
			ticket_base.pop_back();
			break;
		case 6:
			std::cout << "Введите имя: ";
			std::cin >> _name;
			std::cout << "Введите фамилию: ";
			std::cin >> _lastName;
			std::cout << "Введите отчество: ";
			std::cin >> _secondName;

			count = 0;
			it = ticket_base.begin();
			while (it != ticket_base.end())
			{
				it = std::find_if(it, ticket_base.end(), FioFind(Fio(_name, _lastName, _secondName)));
				if (it == ticket_base.end() && count == 0)
				{
					std::cout << "Таких билетов не найдено" << std::endl << std::endl;
					break;
				}
				if (count == 0 && it != ticket_base.end())
					show_table();
				count++;
				std::cout << *it;
				if (it != ticket_base.end())
					it++;
			}
			break;
		case 7:
			for (auto i : ticket_base)
			{
				fout << i;
			}
			return 0;
			break;
		default:
			std::cout << "Такой команды не существует.\n";
			break;
		}
	}
	return 0;
}

void show_table()
{
	std::cout << std::endl;
	std::cout.setf(std::ios::left);
	std::cout.width(30);
	std::cout << "Фамилия";
	std::cout.width(30);
	std::cout << "Имя";
	std::cout.width(30);
	std::cout << "Отчество";
	std::cout.width(30);
	std::cout << "Пункт отправления";
	std::cout.width(30);
	std::cout << "Пункт прибытия";
	std::cout.width(10);
	std::cout << "Цена" << std::endl;
}

Ticket* sortByDepartureStation(Ticket* ticket_base)
{
	for (int step = Ticket::count / 2; step > 0; step /= 2)
		for (int i = step; i < Ticket::count; i++)
			for (int j = i - step; j >= 0 && ticket_base[j].departureStation > ticket_base[j + step].departureStation; j -= step)
				std::swap(ticket_base[j], ticket_base[j + step]);
	return ticket_base;
}