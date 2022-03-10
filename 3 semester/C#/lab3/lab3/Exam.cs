using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace lab3
{
    class Exam: IDateAndCopy, IComparable, IComparer<Exam>
    { 
        public Exam()
        {
            Name = "Exam name";
            Mark = 0;
            Date = System.DateTime.MinValue;
        }
        public Exam(string _name, double _mark, System.DateTime _date)
        {
            Name = _name;
            Mark = _mark;
            Date = new DateTime(_date.Year, _date.Month, _date.Day);
        }

        public override string ToString()
        {
            return Name + " " + Mark + " " + Date.ToString();
        }

        public string Name { get; set; }
        public double Mark { get; set; }

        public DateTime Date { get; set; }

        public object DeepCopy()
        { return (object)(new Exam(Name, Mark, new DateTime(Date.Year, Date.Month, Date.Day))); }

        public int CompareTo(object o)
        {
            if (o is Exam ex)
                return this.Name.CompareTo(ex.Name);
            else
                throw new Exception("Can't compare two objects");
        }

        public int Compare(Exam ex1, Exam ex2)
        {
            if (ex1.Mark > ex2.Mark)
                return 1;
            else if (ex1.Mark < ex2.Mark)
                return -1;
            else 
                return 0;
        }
    } 
}
