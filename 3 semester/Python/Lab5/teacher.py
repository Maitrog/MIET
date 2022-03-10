from Employee import Employee
import datetime


class Teacher(Employee):
    """teacher(lastName, salary, birthday, since)

    Класс преподаватель"""

    def __init__(self, last_name, salary=0, birthday=datetime.datetime(1900, 1, 1), since=""):
        Employee.__init__(self, last_name, salary, birthday)
        self.__since = since  # Область преподавания

    @property
    def since(self):
        return self.__since

    @since.setter
    def since(self, since):
        self.__since = since

    def profession(self):
        """Профессия сотрудника"""
        print("Преподаватель")

    def __str__(self):
        return "{} Предмет: {}".format(Employee.__str__(self), self.__since)
