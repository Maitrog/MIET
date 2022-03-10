using Lab4;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Diagnostics;

namespace Lab4
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
            //-------------TASK 1-------------
            StudentCollection<string> studentCollection1 = new StudentCollection<string>(selector);
            studentCollection1.CollectionName = "studentCollection1";
            StudentCollection<string> studentCollection2 = new StudentCollection<string>(selector);
            studentCollection2.CollectionName = "studentCollection2";
            Journal journal = new Journal();
            
            studentCollection1.StudentChenged += journal.StudentsChanged;
            studentCollection2.StudentChenged += journal.StudentsChanged;

            Student student = new Student("Mikhail", "Tiulnikov", new DateTime(2001, 07, 16), Education.Bachelor, 123);
            studentCollection1.AddStudents(autoGenerator(1).Value);
            studentCollection1.AddStudents(autoGenerator(5).Value);
            studentCollection1.AddStudents(autoGenerator(7).Value);
            studentCollection2.AddStudents(autoGenerator(43).Value);
            studentCollection2.Remove(autoGenerator(43).Value);

            studentCollection2.AddStudents(student);
            student.Group = 388;
            student.Education = Education.SecondEducation;
            student.AddTest(new Test("fff", true));

            studentCollection2.AddStudents(autoGenerator(155).Value);
            studentCollection1.AddStudents(autoGenerator(553).Value);
            studentCollection2.Remove(student);
            student.Group = 355;

            Console.WriteLine(journal.ToString());

        }
    }
}