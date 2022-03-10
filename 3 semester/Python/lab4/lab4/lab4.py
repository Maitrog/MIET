import Employee
import datetime

me = Employee.teacher("Tiulnikov", 1000, datetime.datetime(2001, 7, 16), "Math")
print(me)
print(me.age())
print(me.toFiftyYears())
me.profession()

print("Введите фамилию сотрудника:")
lastName = str(input())
print("Введите оклад сотрудника:")
salary = float(input())
print("Введите дату рождения сотрудника (ГГГГ.MM.ДД):")
str_bd = str(input())
bd = datetime.datetime.strptime(str_bd, "%Y.%m.%d")
emp = Employee.employee(lastName, salary, bd)
print(emp)

simple = Employee.gamer("Kostylev", 5000, datetime.datetime(1997,10,2), "CS:GO", "NAVI")
print(simple)
simple.profession()

omon = Employee.police_man("Korolev", 500, datetime.datetime(1978,7,12), 112)
print(omon)
omon.profession()



