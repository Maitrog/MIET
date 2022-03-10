using lab2;
using System;

namespace lab2
{
    class Program
    {
        static void Main(string[] args)
        {
            //-------------TASK 1-------------
            Console.WriteLine("\n-------------TASK 1-------------");
            Person person1 = new Person("Mikhail", "Tiulnikov", new DateTime(2001, 07, 16));
            Person person2 = new Person("Mikhail", "Tiulnikov", new DateTime(2001, 07, 16));
            Console.WriteLine(person1.Equals(person2).ToString());
            Console.WriteLine($"HashCode student1: {person1.GetHashCode()}\nHashCode student2: {person2.GetHashCode()}");

            //-------------TASK 2-------------
            Console.WriteLine("\n-------------TASK 2-------------");
            Student student1 = new Student("Mikhail", "Tiulnikov", new DateTime(2001, 07, 16), Education.Bachelor, 122);
            student1.AddExams(new Exam("Math", 4, new DateTime(2019, 12, 23)), new Exam("Biology", 4, new DateTime(2019, 12, 23)));
            student1.AddTest(new Test("Math", true));
            Console.WriteLine(student1.ToString());

            //-------------TASK 3-------------
            Console.WriteLine("\n-------------TASK 3-------------");
            Console.WriteLine(student1.Person.ToString());

            //-------------TASK 4-------------
            Console.WriteLine("\n-------------TASK 4-------------");
            Student student_copy = (Student)student1.DeepCopy();
            student1.Group = 356;
            student1.Education = Education.Specialist;
            Console.WriteLine(student1.ToString());
            Console.WriteLine(student_copy.ToString());

            //-------------TASK 5-------------
            Console.WriteLine("\n-------------TASK 5-------------");
            student1.Group = 1;

            //-------------TASK 6-------------
            Console.WriteLine("\n-------------TASK 6-------------");
            foreach (object i in student1.GetExamAndTest())
                Console.WriteLine(i.ToString());

            //-------------TASK 7-------------
            Console.WriteLine("\n-------------TASK 7-------------");
            foreach (Exam i in student1.GetExam(3))
                Console.WriteLine(i.ToString());

            //-------------TASK 8-------------
            Console.WriteLine("\n-------------TASK 8-------------");
            foreach (object i in student1)
                Console.WriteLine(i.ToString());

            //-------------TASK 9-------------
            Console.WriteLine("\n-------------TASK 9-------------");
            foreach (object i in student1.GetPassedSubject())
                Console.WriteLine(i.ToString());

            //-------------TASK 10-------------
            Console.WriteLine("\n-------------TASK 10-------------");
            foreach (object i in student1.GetPassedExamAndTest())
                Console.WriteLine(i.ToString());

        }
    }
}
