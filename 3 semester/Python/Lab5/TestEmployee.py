import unittest
import datetime
from Employee import Employee
from SalaryException import SalaryException
from gamer import Gamer


class TestEmployee(unittest.TestCase):
    def test_name(self):
        with self.assertRaises(Exception):
            Employee("fads2f1", 10005, datetime.datetime(2000, 2, 2))

    def test_salary(self):
        with self.assertRaises(SalaryException):
            Employee("dfgfd", 1, datetime.datetime(2000, 2, 2))

    def test_gamer_profession(self):
        self.assertEqual(Gamer("fads", 10005, datetime.datetime(2000, 2, 2)).profession(), 'Киберспортсмен')


if __name__ == '__main__':
    unittest.main()
