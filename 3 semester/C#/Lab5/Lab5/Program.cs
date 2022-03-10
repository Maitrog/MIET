using Lab5;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Diagnostics;
using System.Net;
using System.IO;

namespace Lab5
{
    class Program
    {
        static string selector(Student st)
        {
            return $"{st.Name} {st.LastName}";
        }

        static KeyValuePair<Person, Student> autoGenerator(int i)
        {
            return new KeyValuePair<Person, Student>(new Person(i.ToString(),i.ToString(), DateTime.MinValue), 
                new Student(i.ToString(), i.ToString(), DateTime.MinValue, (Education)(i % 3), 101+ i % 498));
        }
        static void Main(string[] args)
        {
            //---------------TASK 1---------------
            Console.WriteLine("---------------TASK 1---------------");
            Student student1 = new Student("Mikhail", "Tiulnikov", new DateTime(2001, 07, 16), Education.Bachelor, 122);
            student1.AddExams(new Exam("Math", 4, new DateTime(2019, 12, 23)), new Exam("Biology", 4, new DateTime(2019, 12, 23)));
            student1.AddTest(new Test("Math", true));
            Student copy = student1.DeepCopy();
            Console.WriteLine(student1.ToString());
            Console.WriteLine(copy.ToString());

            //---------------TASK 2---------------
            Console.WriteLine("---------------TASK 2---------------");
            List<Student> st = new List<Student>();
            Student tmp = new Student();

            string curDir = Directory.GetCurrentDirectory();

            Console.WriteLine("Enter file name: ");
            string filename = Console.ReadLine();

            FileInfo usersFile = new FileInfo(@$"{curDir}\{filename}");
            if (!usersFile.Exists)
            {
                Console.WriteLine("Тo such file exists The file will be created.");
                usersFile.Create();
            }
            else
            {
                tmp.Load(@$"{curDir}\{filename}");
            }
            //---------------TASK 3---------------
            Console.WriteLine("---------------TASK 3---------------");
            Console.WriteLine(tmp.ToString());

            //---------------TASK 4---------------
            Console.WriteLine("---------------TASK 4---------------");
            tmp.AddFromConsole();
            tmp.Save(@$"{curDir}\{filename}");
            Console.WriteLine(tmp.ToString());

            //---------------TASK 5---------------
            Console.WriteLine("---------------TASK 5---------------");
            Student.Load(@$"{curDir}\{filename}",ref tmp);
            tmp.AddFromConsole();
            Student.Save(@$"{curDir}\{filename}", tmp);
            Console.WriteLine(tmp.ToString());

        }
    }
}