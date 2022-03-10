//Тюльников Михаил ПИН-22 Вариант 24
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Ticket.h"
#include "Ticket2.h"
#include "Date.h"
#include <vector>

void show_table();
void show_table2();
Ticket* sortByDepartureStation(Ticket*);
void find_ticket(Ticket*, Ticket2*, Fio);
void buy_ticket(Ticket2*);
int ChouseCommand();

int main()
{
	setlocale(0, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::fstream old_base("old_base.txt", std::ios::app);
	old_base.close();

	std::fstream new_base("new_base.txt", std::ios::app);
	new_base.close();

	std::ifstream fin("old_base.txt");

	Ticket* old_ticket_base = new Ticket[0];
	Ticket2* new_ticket_base = new Ticket2[0];

	Ticket* tmp;
	Ticket2* tmp2;
	Fio fio;
	std::string _name;
	std::string _lastname;
	std::string _secondName;
	std::string _arrivalStation;
	std::string _departureStation;
	int _wagonNoumber;
	int _placeNoumber;
	Date _date;
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
		for (int i = 0; i < (Ticket::count - 1) / 2; i++)
		{
			tmp[i] = old_ticket_base[i];
		}
		delete[] old_ticket_base;
		old_ticket_base = tmp;
		old_ticket_base[Ticket::count - 2] = Ticket(_name, _lastname, _secondName, _departureStation, _arrivalStation, _cost);
	}
	fin.close();

	std::ifstream fin2("new_base.txt");
	if (!fin2)
	{
		std::cout << "Ошибка открытия файла.\n";
		return -1;
	}

	while (fin2 >> _name)
	{
		fin2 >> _lastname;
		fin2 >> _secondName;
		fin2 >> _wagonNoumber;
		fin2 >> _placeNoumber;
		fin2 >> _cost;
		fin2 >> _date;

		tmp2 = new Ticket2[Ticket2::count + 1];
		for (int i = 0; i < (Ticket2::count - 1) / 2; i++)
		{
			tmp2[i] = new_ticket_base[i];
		}
		delete[] new_ticket_base;
		new_ticket_base = tmp2;
		new_ticket_base[Ticket2::count - 2] = Ticket2(_name, _lastname, _secondName, _wagonNoumber, _placeNoumber, _cost, _date);
	}
	fin2.close();

	std::ofstream fout("old_base.txt");
	std::ofstream fout2("new_base.txt");

	int k;
	for (;;)
	{
		std::cout << "1.Добавить билет старого образца." << std::endl;
		std::cout << "2.Вывести на экран билеты старого образца." << std::endl;;
		std::cout << "3.Сортировать билеты по пункту отправления." << std::endl;
		std::cout << "4.Поиск билетов по пункту прибытия." << std::endl;
		std::cout << "5.Добавить билет нового образца." << std::endl;
		std::cout << "6.Вывести на экран билеты нового образца." << std::endl;
		std::cout << "7.Найти билет по имени." << std::endl;
		std::cout << "8.Купить билет." << std::endl;
		std::cout << "9.Выход." << std::endl;
		
		k = ChouseCommand();

		switch (k)
		{
		case 1:
			tmp = new Ticket[Ticket::count + 1];
			for (int i = 0; i < (Ticket::count - 1) / 2; ++i)
			{
				tmp[i] = old_ticket_base[i];
			}
			delete[] old_ticket_base;
			old_ticket_base = tmp;
			std::cin >> old_ticket_base[Ticket::count - 1];
			break;
		case 2:
			show_table();
			for (size_t i = 0; i < Ticket::count; ++i)
			{
				std::cout << old_ticket_base[i];
			}
			break;
		case 3:
			old_ticket_base = sortByDepartureStation(old_ticket_base);
			show_table();
			for (size_t i = 0; i < Ticket::count; ++i)
			{
				std::cout << old_ticket_base[i];
			}
			break;
		case 4:
			std::cout << "Введите пункт назначения: ";
			std::cin >> _arrivalStation;
			for (int i = 0; i < Ticket::count; i++)
			{
				if (old_ticket_base[i].findByArrivalStantion(_arrivalStation))
				{
					if (!count)
						show_table();
					std::cout << old_ticket_base[i];
					count++;
				}
			}
			break;
		case 5:
			tmp2 = new Ticket2[Ticket2::count + 1];
			for (int i = 0; i < (Ticket2::count - 1) / 2; ++i)
			{
				tmp2[i] = new_ticket_base[i];
			}
			delete[] new_ticket_base;
			new_ticket_base = tmp2;
			std::cin >> new_ticket_base[Ticket2::count - 1];
			break;
		case 6:
			show_table2();
			for (size_t i = 0; i < Ticket2::count; ++i)
			{
				std::cout << new_ticket_base[i];
			}
			break;
		case 7:
			std::cin >> fio;
			find_ticket(old_ticket_base, new_ticket_base, fio);
			break;
		case 8:
			buy_ticket(new_ticket_base);
		case 9:
			for (size_t i = 0; i < Ticket::count; ++i)
			{
				fout << old_ticket_base[i];
			}
			fout.close();
			delete[] old_ticket_base;
			for (size_t i = 0; i < Ticket2::count; ++i)
			{
				fout2 << new_ticket_base[i];
			}
			fout2.close();
			delete[] new_ticket_base;
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
	std::cout << std::string(154, '-') << std::endl;
}

Ticket* sortByDepartureStation(Ticket* ticket_base)
{
	for (int step = Ticket::count / 2; step > 0; step /= 2)
		for (int i = step; i < Ticket::count; i++)
			for (int j = i - step; j >= 0 && ticket_base[j].departureStation > ticket_base[j + step].departureStation; j -= step)
				std::swap(ticket_base[j], ticket_base[j + step]);
	return ticket_base;
}

void show_table2()
{
	std::cout << std::endl;
	std::cout.setf(std::ios::left);
	std::cout.width(30);
	std::cout << "Фамилия";
	std::cout.width(30);
	std::cout << "Имя";
	std::cout.width(30);
	std::cout << "Отчество";
	std::cout.width(14);
	std::cout << "Номер вагона";
	std::cout.width(13);
	std::cout << "Номер места";
	std::cout.width(12);
	std::cout << "Цена";
	std::cout.width(12);
	std::cout << "Дата" << std::endl;
	std::cout << std::string(133, '-') << std::endl;
}

void find_ticket(Ticket* old_base, Ticket2* new_base, Fio fio)
{
	show_table();
	for (int i = 0; i < Ticket::count; i++)
		if (old_base[i] == fio)
			std::cout << old_base[i];
	show_table2();
	for (int i = 0; i < Ticket2::count; i++)
		if (new_base[i] == fio)
			std::cout << new_base[i];
}
void buy_ticket(Ticket2* new_base)
{
	Ticket2* ticket = new Ticket2;
	bool flag = false;
	while (true)
	{
		std::cin >> *ticket;
		for (int i = 0; i < Ticket2::count - 1; i++)
		{
			if (new_base[i].get_date() == ticket->get_date() && new_base[i].get_wagonNoumber() == ticket->get_wagonNoumber() &&
				new_base[i].get_placeNoumber() == ticket->get_placeNoumber())
				std::cout << "Это место занято." << std::endl;
			else
			{
				Ticket2* tmp2 = new Ticket2[Ticket2::count];
				for (int i = 0; i < (Ticket2::count - 1) / 2; ++i)
				{
					tmp2[i] = new_base[i];
				}
				delete[] new_base;
				new_base = tmp2;
				new_base[Ticket2::count - 1] = *ticket;
				flag = true;
				break;
			}
		}
		if (flag)
			break;
	}
}

int ChouseCommand()
{
	int k;
	while (true)
	{
		try
		{
			std::cout << "Введите команду: ";
			std::cin >> k;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(32768, '\n');
				throw std::invalid_argument("Ошибка ввода!");
			}
			else
			if (k > 9 || k < 1)
				throw std::invalid_argument("Такой команды не существует");
			else
				break;
		}
		catch (std::invalid_argument e)
		{
			std::cout << e.what() << std::endl;
			continue;
		}
	}
	return k;
}