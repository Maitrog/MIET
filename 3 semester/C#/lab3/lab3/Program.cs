using lab3;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Diagnostics;

namespace lab3
{
    class Program
    {
        static string selector(Student st)
        {
            return (st.GetHashCode() / st.Group).ToString();
        }

        static KeyValuePair<Person, Student> autoGenerator(int i)
        {
            return new KeyValuePair<Person, Student>(new Person(i.ToString(),i.ToString(), DateTime.MinValue), 
                new Student(i.ToString(), i.ToString(), DateTime.MinValue, (Education)(i % 3), 101+i));
        }
        static void Main(string[] args)
        {
            //-------------TASK 1-------------
            Console.WriteLine("\n-------------TASK 1-------------");
           
            Student student1 = new Student("Mikhail", "Tiulnikov", new DateTime(2001, 07, 16), Education.Bachelor, 122);
            student1.AddExams(new Exam("Math", 4, new DateTime(2019, 11, 23)), new Exam("Biology", 3, new DateTime(2019, 12, 23)));
            student1.AddTest(new Test("Math", true));
            
            student1.SortExamByName();
            Console.WriteLine(student1.ToString());
            
            student1.SortExamByMark();
            Console.WriteLine(student1.ToString());
           
            student1.SortExamByDate();
            Console.WriteLine(student1.ToString());

            //-------------TASK 2-------------
            Console.WriteLine("\n-------------TASK 2-------------");
           
            Student student2 = new Student("FFFF", "REkov", new DateTime(2001, 07, 16), Education.Specialist, 122);
            student2.AddExams(new Exam("Math", 5, new DateTime(2019, 11, 23)), new Exam("Biology", 4, new DateTime(2019, 12, 23)), new Exam("Physics", 4, new DateTime(2020,11,9)));
            student2.AddTest(new Test("Math", true), new Test("Ecology", false));
           
            Student student3 = new Student("Gkhail", "Eulnikov", new DateTime(2001, 07, 16), Education.Bachelor, 122);
            student3.AddExams(new Exam("Math", 3, new DateTime(2019, 11, 23)), new Exam("Biology", 3, new DateTime(2019, 12, 23)), new Exam("Physics", 2, new DateTime(2020, 11, 9)));
            student3.AddTest(new Test("Math", true), new Test("Ecology", true));
            
            Student student4 = new Student("Rdshail", "Wdalnikov", new DateTime(2001, 07, 16), Education.SecondEducation, 122);
            student4.AddExams(new Exam("Math", 5, new DateTime(2019, 11, 23)), new Exam("Biology", 5, new DateTime(2019, 12, 23)), new Exam("Physics", 4, new DateTime(2020, 11, 9)));
            student4.AddTest(new Test("Math", true), new Test("Ecology", false));
            
            StudentCollection<string> studentCollection = new StudentCollection<string>(new KeySelector<string>(selector));
            studentCollection.AddStudents(student1, student2, student3, student4);
            Console.WriteLine(studentCollection.ToString());
            Console.WriteLine(studentCollection.ToShortString());

            //-------------TASK 3-------------
            Console.WriteLine("\n-------------TASK 3-------------");
            Console.WriteLine($"Max avereg mark: {studentCollection.MaxAvgMark}\n");

            foreach(var i in studentCollection.EducationForm(Education.Bachelor))
            {
                Console.WriteLine(i.Value.ToString());
            }

            foreach(var i in studentCollection.GroupByEducation)
            {
                Console.WriteLine($"\n{i.Key}:");
                foreach(var j in i)
                {
                    Console.WriteLine(j.Value.ToShortString());
                }
            }


            //-------------TASK 4-------------
            Console.WriteLine("\n-------------TASK 4-------------");
            Console.WriteLine("Enter count: ");
            int count;
            count = Console.Read();
            TestCollection<Person, Student> testCollection = new TestCollection<Person, Student>(count, new GenerateElement<Person, Student>(autoGenerator));
            Person startPerson = (Person)testCollection.TKeyList[0].DeepCopy();
            string startString = testCollection.StringList[0];
            Student startStudent = (Student)testCollection.TKeyDict[startPerson].DeepCopy();

            Person middPerson = (Person)testCollection.TKeyList[count / 2].DeepCopy();
            string middString = testCollection.StringList[count / 2];
            Student middStudent = (Student)testCollection.TKeyDict[middPerson].DeepCopy();

            Person endPerson = (Person)testCollection.TKeyList[count - 1].DeepCopy();
            string endString = testCollection.StringList[count - 1];
            Student endStudent = (Student)testCollection.TKeyDict[endPerson].DeepCopy();

            //List<string>
            Console.WriteLine("\nTime for List<string>: ");
            var watch = Stopwatch.StartNew();
            testCollection.StringList.Contains(startString);
            watch.Stop();
            Console.WriteLine($"First: {watch.Elapsed}");

            watch.Restart();
            testCollection.StringList.Contains(middString);
            watch.Stop();
            Console.WriteLine($"Middle: {watch.Elapsed}");

            watch.Restart();
            testCollection.StringList.Contains(endString);
            watch.Stop();
            Console.WriteLine($"Last: {watch.Elapsed}");

            //List<Person>
            Console.WriteLine("\nTime for List<Person>: ");
            watch.Restart();
            testCollection.TKeyList.Contains(startPerson);
            watch.Stop();
            Console.WriteLine($"First: {watch.Elapsed}");

            watch.Restart();
            testCollection.TKeyList.Contains(middPerson);
            watch.Stop();
            Console.WriteLine($"Middle: {watch.Elapsed}");

            watch.Restart();
            testCollection.TKeyList.Contains(endPerson);
            watch.Stop();
            Console.WriteLine($"Last: {watch.Elapsed}");

            //Dictionary<string,Student> (Key)
            Console.WriteLine("\nTime for Dictionary<string, Student> (Key): ");
            watch.Restart();
            testCollection.StringDict.ContainsKey(startString);
            watch.Stop();
            Console.WriteLine($"First: {watch.Elapsed}");

            watch.Restart();
            testCollection.StringDict.ContainsKey(middString);
            watch.Stop();
            Console.WriteLine($"Middle: {watch.Elapsed}");

            watch.Restart();
            testCollection.StringDict.ContainsKey(endString);
            watch.Stop();
            Console.WriteLine($"Last: {watch.Elapsed}");

            //Dictionary<Person,Student> (Key)
            Console.WriteLine("\nTime for Dictionary<Person, Student> (Key): ");
            watch.Restart();
            testCollection.TKeyDict.ContainsKey(startPerson);
            watch.Stop();
            Console.WriteLine($"First: {watch.Elapsed}");

            watch.Restart();
            testCollection.TKeyDict.ContainsKey(middPerson);
            watch.Stop();
            Console.WriteLine($"Middle: {watch.Elapsed}");

            watch.Restart();
            testCollection.TKeyDict.ContainsKey(endPerson);
            watch.Stop();
            Console.WriteLine($"Last: {watch.Elapsed}");

            //Dictionary<string,Student> (Value)
            Console.WriteLine("\nTime for Dictionary<string, Student> (Value): ");
            watch.Restart();
            testCollection.StringDict.ContainsValue(startStudent);
            watch.Stop();
            Console.WriteLine($"First: {watch.Elapsed}");

            watch.Restart();
            testCollection.StringDict.ContainsValue(middStudent);
            watch.Stop();
            Console.WriteLine($"Middle: {watch.Elapsed}");

            watch.Restart();
            testCollection.StringDict.ContainsValue(endStudent);
            watch.Stop();
            Console.WriteLine($"Last: {watch.Elapsed}");

            //Dictionary<Person,Student> (Value)
            Console.WriteLine("\nTime for Dictionary<Person, Student> (Value): ");
            watch.Restart();
            testCollection.TKeyDict.ContainsValue(startStudent);
            watch.Stop();
            Console.WriteLine($"First: {watch.Elapsed}");

            watch.Restart();
            testCollection.TKeyDict.ContainsValue(middStudent);
            watch.Stop();
            Console.WriteLine($"Middle: {watch.Elapsed}");

            watch.Restart();
            testCollection.TKeyDict.ContainsValue(endStudent);
            watch.Stop();
            Console.WriteLine($"Last: {watch.Elapsed}");
        }
    }
}
