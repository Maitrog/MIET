class SalaryException(Exception):
    """description of class"""

    def __init__(self, min_salary, self_salary):
        self.__minSalary = min_salary
        self.__selfSalary = self_salary

    def __str__(self):
        return "Оклад не может принимать значение меньше {}. Введенное значение {}".format(self.__minSalary,
                                                                                           self.__selfSalary)
