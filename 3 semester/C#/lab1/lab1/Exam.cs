using System;
using System.Collections.Generic;
using System.Text;

namespace lab1
{
    class Exam
    {
        private string name;
        private double mark;
        private System.DateTime date;

        public Exam()
        {
            name = "Exam name";
            mark = 0;
            date = System.DateTime.MinValue;
        }
        public Exam(string _name, int _mark, System.DateTime _date)
        {
            name = _name;
            mark = _mark;
            date = new DateTime(_date.Year, _date.Month, _date.Day);
        }

        public override string ToString()
        {
            return name + " " + mark + " " + date.ToString();
        }

        public string Name { get; set; }
        //public double Mark
        //{
        //    get
        //    {
        //        return mark;
        //    }
        //    set
        //    {
        //        mark = value;
        //    }
        //}
        public double Mark { get; set; }
    }
}
