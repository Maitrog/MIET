import datetime
from SalaryException import SalaryException


class Employee:
    """employee(lastName, salary, birthday)

    Класс сотрудник"""

    def __init__(self, last_name, salary=0, birthday=datetime.datetime(1900, 1, 1)):
        if not last_name.isalpha():
            self.__last_name = ""
            raise Exception("Фамилия может содержать только буквы.")
        self.__last_name = last_name
        if salary < 1000:
            raise SalaryException(1000, salary)
        self.__salary = salary
        self.__birthday = birthday

    def __del__(self):
        print(self.__last_name, "удален из памяти")

    @property
    def salary(self):
        return self.__salary

    @salary.setter
    def salary(self, salary):
        if salary < 0:
            raise Exception("Оклад не может принимать значение меньше 0.")
        self.__salary = salary

    @property
    def last_name(self):
        return self.__last_name

    @last_name.setter
    def last_name(self, last_name):
        if not last_name.isalpha():
            raise Exception("Фамилия может содержать только буквы.")
        self.__last_name = last_name

    @property
    def birthday(self):
        return self.__birthday

    @birthday.setter
    def birthday(self, birthday):
        self.__birthday = birthday

    def age(self):
        """Возрасть сотрудника"""
        now = datetime.datetime.now()
        if self.__birthday.month < now.month:
            return "{} лет".format(now.year - self.__birthday.year)
        elif self.__birthday.month == now.month:
            if self.__birthday.day <= now.day:
                return "{} лет".format(now.year - self.__birthday.year)
            else:
                return "{} лет".format(now.year - self.__birthday.year - 1)
        else:
            return "{} лет".format(now.year - self.__birthday.year - 1)

    def to_fifty_years(self):
        """Количество дней до 50 лет"""
        fifty_age = datetime.datetime(self.__birthday.year + 50, self.__birthday.month, self.__birthday.day)
        return "50 лет через {} дней".format((fifty_age - self.__birthday).days)

    def profession(self):
        """Профессия сотрудника"""
        print("Сотрудник")
        return 'Сотрудник'

    def __str__(self):
        return "{} {} Имеет оклад {}".format(self.__last_name, self.__birthday, self.__salary)
