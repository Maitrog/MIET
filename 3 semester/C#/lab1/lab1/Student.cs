using System;
using System.Collections.Generic;
using System.Text;

namespace lab1
{
    class Student
    {
        private Person person;
        private Education education;
        private int group;
        private Exam[] listExam;

        public Student()
        {
            person = new Person();
            education = Education.Bachelor;
            group = 22;
            listExam = new Exam[0];
        }

        public Student(Person _person, Education _education, int _group)
        {
            person = new Person(_person.Name, _person.Last_Name, new DateTime(_person.Birthday.Year, _person.Birthday.Month, _person.Birthday.Day));
            education = _education;
            group = _group;
            listExam = new Exam[0];
        }

        public Person Person
        {
            get { return person; }
            set { person = value; }
        }

        public Education Education
        {
            get { return education; }
            set { education = value; }
        }

        public int Group
        { 
            get { return group; }
            set { group = value; }
        }

        public Exam[] ListExam
        {
            get { return listExam; }
        }

        public double AvgMark()
        {
            double sumMark = 0;
            for (int i = 0; i < listExam.Length; i++)
                sumMark += listExam[i].Mark;
            if (sumMark == 0)
                return 0;
            return sumMark / listExam.Length;
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
            Exam[] tmp = listExam;
            listExam = new Exam[exams.Length + listExam.Length];
            for (int i = 0; i < tmp.Length; ++i)
            {
                listExam[i] = tmp[i];
            }
            for (int i = tmp.Length; i < listExam.Length; ++i)
            {
                listExam[i] = exams[i - tmp.Length];
            }
        }

        public override string ToString()
        {
            string str;
            str = person.ToString() + " " + education.ToString() + " Group: " + group + '\n' + "Exam:\n";
            for(int i = 0; i<listExam.Length; ++i)
            {
                str += listExam[i].ToString() + '\n';
            }
            return str;
        }

        virtual public string ToShortString()
        {
            return person.ToString() + " " + education.ToString() + " Group: " + group + " Avereg mark: " + this.AvgMark();
        }
    }
}
