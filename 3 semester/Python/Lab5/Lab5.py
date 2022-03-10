# Тюльников Михаил ПИН-22
from Employee import Employee
from gamer import Gamer
from policeman import PoliceMan
from teacher import Teacher
from TestEmployee import TestEmployee

import datetime
import pickle


def add_employee(employees_list):
    try:
        last_name = str(input("Введите фамилию сотрудника:"))
        salary = float(input("Введите оклад сотрудника:"))
        str_bd = str(input("Введите дату рождения сотрудника (ГГГГ.MM.ДД):"))
        bd = datetime.datetime.strptime(str_bd, "%Y.%m.%d")
        type_of_emp = int(
            input("Выберите тип сотрудника: 1 - сотрудник, 2 - учитель, 3 - полицейский, 4 - киберспортсмен:"))
        assert 5 > type_of_emp > 0, 'Неправильный выбор команды'
        if type_of_emp == 1:
            emp = Employee(last_name, salary, bd)
        elif type_of_emp == 2:
            since = str(input("Введите специальность преподавателя:"))
            emp = Teacher(last_name, salary, bd, since)
        elif type_of_emp == 3:
            dep = int(input("Введите департамент:"))
            emp = PoliceMan(last_name, salary, bd, dep)
        elif type_of_emp == 4:
            command = str(input("Введите название команды игрока:"))
            game = str(input("Введите игру игрока:"))
            emp = Gamer(last_name, salary, bd, game, command)
        else:
            raise ValueError()
    except (TypeError, ValueError):
        print("Некорректный ввод")
        return employees_list
    except Exception as ex:
        print(ex)
        return employees_list
    assert emp is not None, 'Попытка использования emp, когда он равен None'
    employees_list.append(emp)
    return employees_list


def print_list(employee_list):
    for emp in employee_list:
        assert emp is not None, 'Попытка использования emp, когда он равен None'
        print(emp)
        print(emp.age())
        print(emp.to_fifty_years())
        emp.profession()


employees = list()
try:
    file = open("lab5.dat", "rb")
    employees = pickle.load(file)
    file.close()
except EOFError as e:
    print("Файл пуст")
    file.close()
except FileNotFoundError as e:
    print("Файл не найден")

while True:
    print("1.Добавть сотрудника")
    print("2.Вывести список сотрудников на экран")
    print("3.Выход")
    try:
        choice = int(input())
        assert 5 > choice > 0, 'Неправильный выбор команды'
        if choice == 1:
            employees = add_employee(employees)
        elif choice == 2:
            print_list(employees)
        elif choice == 3:
            file = open("lab5.dat", "wb")
            pickle.dump(employees, file)
            file.close()
            break
        else:
            print("Такой команды не существует.")
    except (TypeError, ValueError) as e:
        print("Некорректный ввод")
    except FileNotFoundError as e:
        print("Файл не найден")
