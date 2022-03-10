//Тюльников Михаил ПИН-22 Вариант 24
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Ticket.h"

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
	Ticket* ticket_base = new Ticket[0];
	Ticket* tmp;
	std::string _name;
	std::string _lastname;
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
		fin >> _lastname;
		fin >> _secondName;
		fin >> _arrivalStation;
		fin >> _departureStation;
		fin >> _cost;

		tmp = new Ticket[Ticket::count + 1];
		for (int i = 0; i < (Ticket::count -1) / 2; i++)
		{
			tmp[i] = ticket_base[i];
		}
		delete[] ticket_base;
		ticket_base = tmp;
		ticket_base[Ticket::count - 2] = Ticket(_name, _lastname, _secondName, _departureStation, _arrivalStation, _cost);
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
		std::cout << "5.Выход." << std::endl;
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
			tmp = new Ticket[Ticket::count + 1];
			for (int i = 0; i < (Ticket::count - 1) / 2; ++i)
			{
				tmp[i] = ticket_base[i];
			}
			delete[] ticket_base;
			ticket_base = tmp;
			std::cin >> ticket_base[Ticket::count - 1];
			break;
		case 2:
			show_table();
			for (size_t i = 0; i < Ticket::count; ++i)
			{
				std::cout << ticket_base[i];
			}
			break;
		case 3:
			ticket_base = sortByDepartureStation(ticket_base);
			show_table();
			for (size_t i = 0; i < Ticket::count; ++i)
			{
				std::cout << ticket_base[i];
			}
			break;
		case 4:
			std::cout << "Введите пункт назначения: ";
			std::cin >> _arrivalStation;
			for (int i = 0; i < Ticket::count; i++)
			{
				if (ticket_base[i].findByArrivalStantion(_arrivalStation))
				{
					if (!count)
						show_table();
					std::cout << ticket_base[i];
					count++;
				}
			}
			break;
		case 5:
			for (size_t i = 0; i < Ticket::count; ++i)
			{
				fout << ticket_base[i];
			}
			fout.close();
			delete[] ticket_base;
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