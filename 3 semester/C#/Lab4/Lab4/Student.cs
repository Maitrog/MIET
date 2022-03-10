using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;

namespace Lab4
{
    class Student : Person, IDateAndCopy, IEnumerable, INotifyPropertyChanged
    {
        private Education education;
        private int group;
        private List<Exam> listExam;
        private List<Test> listTest;

        new public event PropertyChangedEventHandler PropertyChanged;

        public Student():base("", "", DateTime.MinValue)
        {
            Education = Education.Bachelor;
            Group = 122;
            listExam = new List<Exam>();
            listTest = new List<Test>();
        }
        
        public Student(string _name, string _lastname, DateTime _birthday, Education _education, int _group)
            :base(_name,_lastname, new DateTime(_birthday.Year, _birthday.Month, _birthday.Day))
        {
            Education = _education;
            try
            {
                if (_group < 101 || _group > 599)
                    throw (new Exception("Group noumber out of range. Corrected range from 101 to 599"));
                Group = _group;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            listExam = new List<Exam>();
            listTest = new List<Test>();
        }

        public Student(Person _person, Education _education, int _group):base(_person.Name, _person.LastName, _person.Date)
        {
            Education = _education;
            try
            {
                if (_group < 101 || _group > 599)
                    throw (new Exception("Group noumber out of range. Corrected range from 101 to 599"));
                Group = _group;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            listExam = new List<Exam>();
            listTest = new List<Test>();
        }

        public Education Education
        {
            get { return education; }
            set 
            { 
                education = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Education"));
            }
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
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Group"));
                }
                catch(Exception e)
                {
                    Console.WriteLine(e.Message);
                }
            }
        }

        public List<Exam> ListExam
        {
            get { return listExam; }
            set 
            { 
                listExam = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("ListExam"));
            }
        }

        public List<Test> ListTest
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
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Person"));
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

        public void SortExamByMark()
        {
            ListExam.Sort(new Exam());
        }

        public void SortExamByName()
        {
            ListExam.Sort();
        }

        public void SortExamByDate()
        {
            ListExam.Sort(new ExamComparer());
        }

        public static bool operator ==(Student st1, Student st2)
        {
            if (st1.ListExam.Count != st2.ListExam.Count)
                return false;
            for (int i = 0; i < st1.ListExam.Count; i++)
            {
                if (st1.ListExam[i] != st2.ListExam[i])
                    return false;
            }
            if (st1.ListTest.Count != st2.ListTest.Count)
                return false;
            for (int i = 0; i < st1.ListTest.Count; i++)
            {
                if (st1.ListTest[i] != st2.ListTest[i])
                    return false;
            }
            return st1.Person == st2.Person && st1.education == st2.education && st1.group == st2.group;
        }

        public static bool operator !=(Student st1, Student st2)
        {
            bool check = false;
            if (st1.ListExam.Count == st2.ListExam.Count)
                return false;
            for (int i = 0; i < st1.ListExam.Count; i++)
            {
                if (st1.ListExam[i] != st2.ListExam[i])
                {
                    check = true;
                    break;
                }
            }
            if (!check)
            {
                if (st1.ListTest.Count == st2.ListTest.Count)
                    return false;
                for (int i = 0; i < st1.ListTest.Count; i++)
                {
                    if (st1.ListTest[i] == st2.ListTest[i])
                    {
                        check = true;
                        break;
                    }
                }
            }
            return st1.Person == st2.Person && st1.education == st2.education && st1.group == st2.group && check;
        }
    }

}