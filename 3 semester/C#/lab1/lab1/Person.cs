using System;
using System.Collections.Generic;
using System.Text;

namespace lab1
{
    class Person
    {
        private string name;
        private string last_name;
        private System.DateTime birthday;

        public Person()
        {
            name = "";
            last_name = "";
            birthday = DateTime.MinValue;
        }
        public Person(string _name, string _last_name, System.DateTime _birthday)
        {
            name = _name;
            last_name = _last_name;
            birthday = new DateTime(_birthday.Year, _birthday.Month, _birthday.Day);
        }


        public string Name
        {
            get { return name; }

            set { name = value; }

        }

        public string Last_Name
        {
            get { return last_name; }
            set { last_name = value; }
        }

        public System.DateTime Birthday
        {
            get { return birthday; }
            set
            {
                birthday = value;
            }
        }

        public override string ToString()
        {
            return name + " " + last_name + " " + birthday.ToString();
        }
    }
}
