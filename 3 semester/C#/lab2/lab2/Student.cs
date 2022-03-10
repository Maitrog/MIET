using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace lab2
{
    class Student: Person, IDateAndCopy, IEnumerable
    {
        private Education education;
        private int group;
        private ArrayList listExam;
        private ArrayList listTest;

        public Student():base("", "", new DateTime(0,0,0))
        {
            Education = Education.Bachelor;
            Group = 22;
            listExam = new ArrayList();
            listTest = new ArrayList();
        }

        public Student(string _name, string _lastname, DateTime _birthday, Education _education, int _group)
            :base(_name,_lastname, new DateTime(_birthday.Year, _birthday.Month, _birthday.Day))
        {
            Education = _education;
            Group = _group;
            listExam = new ArrayList();
            listTest = new ArrayList();
        }

        public Student(Person _person, Education _education, int _group):base(_person.Name, _person.LastName, _person.Date)
        {
            Education = _education;
            Group = _group;
            listExam = new ArrayList();
            listTest = new ArrayList();
        }

        public Education Education
        {
            get { return education; }
            set { education = value; }
        }

        public int Group
        { 
            get { return group; }
            set
            {
                try
                {
                    if (value < 101 || value > 599)
                        throw (new Exception("Group noumber out of range. Corrected range from 101 to 599"));
                    group = value;
                }
                catch(Exception e)
                {
                    Console.WriteLine(e.Message);
                }
            }
        }

        public ArrayList ListExam
        {
            get { return listExam; }
            set { listExam = value; }
        }

        public ArrayList ListTest
        {
            get { return listTest; }
        }

        public Person Person
        {
            get { return new Person(Name, LastName, new DateTime(Date.Year, Date.Month, Date.Day)); }
            set
            {
                Name = value.Name;
                LastName = value.LastName;
                Date = new DateTime(value.Date.Year, value.Date.Month, value.Date.Day);
            }
        }

        public double AvgMark()
        {
            double sumMark = 0;
            foreach(object i in listExam)
                sumMark += ((Exam)i).Mark;
            if (sumMark == 0)
                return 0;
            return sumMark / listExam.Count;
        }

        public bool this[Education e]
        {
            get
            {
                return education == e;
            }
        }

        public void AddExams(params Exam[] exams)
        {
            for(int i = 0; i < exams.Length; ++i)
                listExam.Add(exams[i]);
        }

        public void AddTest(params Test[] test)
        {
            for (int i = 0; i < test.Length; ++i)
                listTest.Add(test[i]);
        }

        public override string ToString()
        {
            string str;
            str = Person.ToString() + " " + education.ToString() + " Group: " + group + '\n' + "Exam:\n";
            for(int i = 0; i<listExam.Count; ++i)
            {
                str += listExam[i].ToString() + '\n';
            }
            str += "Test:\n";
            for (int i = 0; i < listTest.Count; ++i)
                str += listTest[i].ToString() + '\n';
            return str;
        }

        virtual public string ToShortString()
        {
            return Person.ToString() + " " + education.ToString() + " Group: " + group + " Avereg mark: " + this.AvgMark();
        }

        public override object DeepCopy()
        {
            Student new_student = (new Student(Person, Education, Group));
            foreach(Exam i in listExam)
                new_student.AddExams((Exam)i.DeepCopy());
            foreach (Test i in listTest)
                new_student.AddTest((Test)i.DeepCopy());
            return (object)(new_student);
        }

        public IEnumerable GetExamAndTest()
        {
            for (int i = 0; i < listExam.Count; i++)
                yield return listExam[i];
            for (int i = 0; i < listTest.Count; i++)
                yield return listTest[i];
        }

        public IEnumerable GetExam(int _mark)
        {
            for (int i = 0; i < listExam.Count; ++i)
                if (((Exam)listExam[i]).Mark > _mark)
                    yield return listExam[i];
        }

        public IEnumerator GetEnumerator()
        {
            return new StudentEnumerator(ListExam, ListTest);
        }

        public IEnumerable GetPassedSubject()
        {
            foreach(Exam i in ListExam)
            {
                if (i.Mark > 2)
                    yield return i;
            }
            foreach(Test i in ListTest)
            {
                if (i.Credit)
                    yield return i;
            }
        }   
        public IEnumerable GetPassedExamAndTest()
        {
            foreach(Test i in ListTest)
                foreach (Exam j in ListExam)
                    if (i.Name == j.Name && i.Credit && j.Mark > 2)
                        yield return i;
        }
    }
}