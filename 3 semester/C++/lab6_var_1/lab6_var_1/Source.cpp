#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Account.h"
#include "Credit.h"
#include "Deposit.h"
#include "Fio.h"


void show_deposit_table_header();
void show_credit_table_header();
void find_account(Deposit*, Credit*, Fio);
int ChouseCommand();
Deposit* SortByDeposit(Deposit*);


int main()
{
	setlocale(0, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::fstream deposit_base_f("deposit_base.txt", std::ios::app);
	deposit_base_f.close();

	std::fstream credit_base_f("credit_base.txt", std::ios::app);
	credit_base_f.close();

	std::ifstream fin("deposit_base.txt");
	Deposit* deposit_base = new Deposit[0];
	Credit* credit_base = new Credit[0];
	Deposit* dep_tmp;
	Credit* cr_tmp;
	std::string _name;
	std::string _lastname;
	std::string _secondName;
	int _number;
	double _sum;
	double _percent;
	double _term;
	double _monthlyPayment;
	int count = 0;
	Fio _fio;

	if (!fin)
	{
		std::cout << "������ �������� �����.\n";
		return -1;
	}

	while (fin >> _number)
	{
		fin >> _name;
		fin >> _lastname;
		fin >> _secondName;
		fin >> _sum;

		dep_tmp = new Deposit[Deposit::count + 1];
		for (int i = 0; i < (Deposit::count - 1) / 2; i++)
		{
			dep_tmp[i] = deposit_base[i];
		}
		delete[] deposit_base;
		deposit_base = dep_tmp;
		deposit_base[Deposit::count - 2] = Deposit(Fio(_name, _lastname, _secondName), _number, _sum);
	}
	fin.close();

	std::ifstream fin2("credit_base.txt");
	if (!fin2)
	{
		std::cout << "������ �������� �����.\n";
		return -1;
	}

	while (fin2 >> _number)
	{
		fin2 >> _name;
		fin2 >> _lastname;
		fin2 >> _secondName;
		fin2 >> _sum;
		fin2 >> _percent;
		fin2 >> _term;
		fin2 >> _monthlyPayment;

		cr_tmp = new Credit[Credit::count + 1];
		for (int i = 0; i < (Credit::count - 1) / 2; i++)
		{
			cr_tmp[i] = credit_base[i];
		}
		delete[] credit_base;
		credit_base = cr_tmp;
		credit_base[Credit::count - 2] = Credit(Fio(_name, _lastname, _secondName), _number, _sum, _percent, _term);
	}
	fin2.close();

	std::ofstream fout("deposit_base.txt");
	std::ofstream fout2("credit_base.txt");

	int k;
	for (;;)
	{
		std::cout << "1.�������� ���������� ����." << std::endl;
		std::cout << "2.������� �� ����� ��� ���������� �����." << std::endl;;
		std::cout << "3.����������� ���������� ����� �� ���������� ����� ��������." << std::endl;
		std::cout << "4.����� ����������� ����� �� ������." << std::endl;
		std::cout << "5.�������� ����� �� ����." << std::endl;
		std::cout << "6.������� ����� �� �����." << std::endl;
		std::cout << "7.�������� ������." << std::endl;
		std::cout << "8.������� �� ����� ��� �������." << std::endl;
		std::cout << "9.����� �� �������." << std::endl;
		std::cout << "10.����� �� ����� � ����� ����� ������." << std::endl;
		std::cout << "11.�����." << std::endl;
		
		k = ChouseCommand();

		switch (k)
		{
		case 1:
			dep_tmp = new Deposit[Deposit::count + 1];
			for (int i = 0; i < (Deposit::count - 1) / 2; ++i)
			{
				dep_tmp[i] = deposit_base[i];
			}
			delete[] deposit_base;
			deposit_base = dep_tmp;
			std::cin >> deposit_base[Deposit::count - 1];
			break;
		case 2:
			show_deposit_table_header();
			for (size_t i = 0; i < Deposit::count; ++i)
			{
				std::cout << deposit_base[i] << std::endl;
			}
			break;
		case 3:
			deposit_base = SortByDeposit(deposit_base);
			show_deposit_table_header();
			for (size_t i = 0; i < Deposit::count; ++i)
			{
				std::cout << deposit_base[i] << std::endl;
			}
			break;
		case 4:
			try
			{
				std::cout << "������� ����� �����: ";
				std::cin >> _number;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(32768, '\n');
					throw std::invalid_argument("������ �����!");
				}

				for (int i = 0; i < Deposit::count; i++)
				{
					if (deposit_base[i].get_number() == _number)
					{
						show_deposit_table_header();
						std::cout << deposit_base[i] << std::endl;
						break;
					}
				}
			}
			catch (std::invalid_argument e)
			{
				std::cout << e.what() << std::endl;
				continue;
			}
			break;
		case 5:
			show_deposit_table_header();
			try
			{
				for (size_t i = 0; i < Deposit::count; ++i)
				{
					std::cout << deposit_base[i] << std::endl;
				}

				std::cout << "������� ����� �����, � �������� ������ �������� �����: ";
				std::cin >> _number;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(32768, '\n');
					throw std::invalid_argument("������ �����!");
				}

				std::cout << "������� �����, ������� ������ ��������: ";
				std::cin >> _sum;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(32768, '\n');
					throw std::invalid_argument("������ �����!");
				}
				if (_sum < 0)
					throw std::invalid_argument("����� �� ����� ���� �������������");
				for (int i = 0; i < Deposit::count; i++)
				{
					if (deposit_base[i].get_number() == _number)
					{
						deposit_base[i] = deposit_base[i] + _sum;
						break;
					}
				}
			}
			catch (std::invalid_argument e)
			{
				std::cout << e.what() << std::endl;
				continue;
			}
			break;
		case 6:
			show_deposit_table_header();

			for (size_t i = 0; i < Deposit::count; ++i)
			{
				std::cout << deposit_base[i] << std::endl;
			}

			try
			{
				std::cout << "������� ����� �����, � �������� ������ ������� �����: ";
				std::cin >> _number;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(32768, '\n');
					throw std::invalid_argument("������ �����!");
				}

				std::cout << "������� �����, ������� ������ �������: ";
				std::cin >> _sum;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(32768, '\n');
					throw std::invalid_argument("������ �����!");
				}
				if (_sum <= 0)
					throw std::invalid_argument("����� ������ ���� �������������");

				for (int i = 0; i < Deposit::count; i++)
				{
					if (deposit_base[i].get_number() == _number)
					{
						if (_sum > deposit_base[i].get_deposit())
							throw std::invalid_argument("�������� ����� ��������� ����� �� �����");
						deposit_base[i] = deposit_base[i] + (-_sum);
						break;
					}
				}
			}
			catch (std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		case 7:
			cr_tmp = new Credit[Credit::count + 1];
			for (int i = 0; i < (Credit::count - 1) / 2; ++i)
			{
				cr_tmp[i] = credit_base[i];
			}
			delete[] credit_base;
			credit_base = cr_tmp;
			std::cin >> credit_base[Credit::count - 1];
			break;
		case 8:
			show_credit_table_header();
			for (size_t i = 0; i < Credit::count; ++i)
			{
				std::cout << credit_base[i] << std::endl;
			}
			break;
		case 9:
			show_credit_table_header();
			for (size_t i = 0; i < Credit::count; ++i)
			{
				std::cout << credit_base[i] << std::endl;
			}

			try
			{
				std::cout << "������� ����� �����, �� ������� ������ ������ �����: ";
				std::cin >> _number;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(32768, '\n');
					throw std::invalid_argument("������ �����!");
				}

				std::cout << "������� �����, ������� ������ ������: ";
				std::cin >> _sum;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(32768, '\n');
					throw std::invalid_argument("������ �����!");
				}
				if (_sum <= 0)
					throw std::invalid_argument("����� ������ ���� �������������");

				for (int i = 0; i < Credit::count; i++)
				{
					if (credit_base[i].get_number() == _number)
					{
						credit_base[i].set_credit(credit_base[i].get_credit() - _sum);
						break;
					}
				}
			}
			catch (std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		case 10:
			try
			{
				std::cin >> _fio;
				find_account(deposit_base, credit_base, _fio);
			}
			catch (std::bad_cast& e)
			{
				std::cerr << "� ����� ����� ����������� ������ �����" << std::endl;
				continue;
			}
			break;
		case 11:
			for (size_t i = 0; i < Deposit::count; ++i)
			{
				fout << deposit_base[i];
			}
			fout.close();
			delete[] deposit_base;
			for (size_t i = 0; i < Credit::count; ++i)
			{
				fout2 << credit_base[i];
			}
			fout2.close();
			delete[] credit_base;
			return 0;
			break;
		default:
			std::cout << "����� ������� �� ����������.\n";
			break;
		}
	}
	return 0;
}

Deposit* SortByDeposit(Deposit* deposit_base)
{
	for (int step = Deposit::count / 2; step > 0; step /= 2)
		for (int i = step; i < Deposit::count; i++)
			for (int j = i - step; j >= 0 && deposit_base[j].get_deposit() < deposit_base[j + step].get_deposit(); j -= step)
				std::swap(deposit_base[j], deposit_base[j + step]);
	return deposit_base;
}

void show_deposit_table_header()
{
	std::cout << std::endl;
	std::cout.setf(std::ios::left);
	std::cout.width(15);
	std::cout << "����� �����";
	std::cout.width(30);
	std::cout << "�������";
	std::cout.width(30);
	std::cout << "���";
	std::cout.width(30);
	std::cout << "��������";
	std::cout.width(10);
	std::cout << "�������" << std::endl;
	std::cout << std::string(115, '-') << std::endl;
}

void show_credit_table_header()
{
	std::cout << std::endl;
	std::cout.setf(std::ios::left);
	std::cout.width(15);
	std::cout << "����� �����";
	std::cout.width(30);
	std::cout << "�������";
	std::cout.width(30);
	std::cout << "���";
	std::cout.width(30);
	std::cout << "��������";
	std::cout.width(15);
	std::cout << "����� �������";
	std::cout.width(10);
	std::cout << "�������";
	std::cout.width(10);
	std::cout << "����";
	std::cout.width(10);
	std::cout << "���������� �����";
	std::cout << std::endl << std::string(130, '-') << std::endl;
}

void find_account(Deposit* deposit_base, Credit* credit_base, Fio fio)
{
	show_deposit_table_header();
	for (int i = 0; i < Deposit::count; i++)
		if (deposit_base[i].get_name() == fio)
			std::cout << deposit_base[i] << std::endl;
	std::cout << std::endl;

	show_credit_table_header();
	for (int i = 0; i < Credit::count; i++)
		if (credit_base[i].get_name() == fio)
			std::cout << credit_base[i] << std::endl;
	std::cout << std::endl;
}

int ChouseCommand()
{
	int k;
	while (true)
	{
		try
		{
			std::cout << "������� �������: ";
			std::cin >> k;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(32768, '\n');
				throw std::invalid_argument("������ �����!");
			}
			else
				if (k > 11 || k < 1)
					throw std::invalid_argument("����� ������� �� ����������");
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