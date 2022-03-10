from Employee import Employee
import datetime


class PoliceMan(Employee):
    """police_man(lastName, salary, birthday, department)

    Класс сотрудник полиции"""

    def __init__(self, last_name, salary=0, birthday=datetime.datetime(1900, 1, 1), department=1):
        Employee.__init__(self, last_name, salary, birthday)
        if department < 1:
            raise Exception("Номер департамента не может быть меньше 1")
        self.__department = department  # Департамент полиции

    @property
    def department(self):
        return self.__department

    @department.setter
    def department(self, department):
        if department < 1:
            raise Exception("Номер департамента не может быть меньше 1")
        self.__department = department  # Департамент полиции

    def __str__(self):
        return "{} Департамент: {}".format(Employee.__str__(self), self.__department)
