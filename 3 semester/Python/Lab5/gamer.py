from Employee import Employee
import datetime


class Gamer(Employee):
    """gamer(lastName, salary, birthday, game, command)

    Класс киберспортсмен"""

    def __init__(self, last_name, salary=0, birthday=datetime.datetime(1900, 1, 1), game="", command=""):
        Employee.__init__(self, last_name, salary, birthday)
        self.__game = game  # Название игры
        self.__command = command  # Название команды

    @property
    def game(self):
        return self.__game

    @game.setter
    def game(self, game):
        self.__game = game

    @property
    def command(self):
        return self.__command

    @command.setter
    def command(self, command):
        self.__command = command

    def profession(self):
        """Профессия сотрудника"""
        print("Киберспортсмен")
        return 'Киберспортсмен'

    def __str__(self):
        return "{}\nИграет в {} за {}".format(Employee.__str__(self), self.__game, self.__command)
