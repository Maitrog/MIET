import datetime
class employee:
    """employee(lastName, salary, birthday)

    Класс сорудник"""

    def __init__(self, lastName, salary = 0, birthday = datetime.datetime(1900,1,1)):
        self.__lastName = lastName #фамилия
        self.__salary = salary     #оклад
        self.__birthday = birthday #день рождения

    def __del__(self):
        print(self.__lastName, "удален из памяти")

    @property
    def salary(self):
        return self.__salary

    @salary.setter
    def salary(self, salary):
        if _salary < 0:
            print("Оклад не может принимать значение меньше 0.")
        else:
            self.__salary = salary

    @property
    def lastName(self):
        return self.__lastName

    @lastName.setter
    def lastName(self, lastName):
        self.__lastName = lastName

    @property
    def birthday(self):
        return birthday

    @birthday.setter
    def birthday(self, birthday):
        self.__birthday = birthday

    def age(self):
        "Возрасть сотрудника"
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

    def toFiftyYears(self):
        "Количество дней до 50 лет"
        fiftyAge = datetime.datetime(self.__birthday.year + 50, self.__birthday.month, self.__birthday.day)
        return "50 лет через {} дней".format((fiftyAge - self.__birthday).days)

    def profession(self):
        "Профессия сотрудника"
        print("Сотрудник")
         
    def __str__(self):
        return "{} {} Имеет оклад {}".format(self.__lastName, self.__birthday, self.__salary)

    




class teacher(employee):
    """teacher(lastName, salary, birthday, since)

    Класс преподаватель"""
    def __init__(self, lastName, salary = 0, birthday = datetime.datetime(1900,1,1), since = ""):
        employee.__init__(self, lastName, salary, birthday)
        self.__since = since #Область преподавания

    @property
    def since(self):
        return self

    @since.setter
    def group(self, group):
        self.__since = since

    def profession(self):
        "Профессия сотрудника"
        print("Преподаватель")

    def __str__(self):
        return "{}\nГруппы: {}".format(employee.__str__(self), self.__since)


class police_man(employee):
    """police_man(lastName, salary, birthday, department)

    Класс сотрудник полиции"""
    def __init__(self, lastName, salary = 0, birthday = datetime.datetime(1900,1,1), department = 1):
        employee.__init__(self, lastName, salary, birthday)
        self.__department = department #Департамент полиции

    @property
    def department(self):
        return self.__department

    @department.setter
    def department(self, department):
        self.__department = department

    def __str__(self):
        return "{} Департамент: {}".format(employee.__str__(self), self.__department)


class gamer(employee):
    """gamer(lastName, salary, birthday, game, comand)

    Класс киберспортсмен"""
    def __init__(self, lastName, salary = 0, birthday = datetime.datetime(1900,1,1), game = "", comand = ""):
        employee.__init__(self,lastName, salary, birthday)
        self.__game = game      #Название игры
        self.__comand = comand  #Название команды

    @property
    def game(self):
        return self.__game

    @game.setter
    def game(self, game):
        self.__game = game

    @property
    def comand(self):
        return comand

    @comand.setter
    def comand(self, comand):
        self.__comand = comand

    def profession(self):
        "Профессия сотрудника"
        print("Киберспортсмен")

    def __str__(self):
        return "{}\nИграет в {} за {}".format(employee.__str__(self), self.__game, self.__comand)