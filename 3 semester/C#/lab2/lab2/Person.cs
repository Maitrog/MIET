using System;
using System.Collections.Generic;
using System.Text;

namespace lab2
{
    class Person: IDateAndCopy
    {
        protected string name;
        protected string lastName;
        protected System.DateTime birthday;

        public Person()
        {
            name = "";
            lastName = "";
            birthday = DateTime.MinValue;
        }
        public Person(string _name, string _last_name, System.DateTime _birthday)
        {
            name = _name;
            lastName = _last_name;
            birthday = new DateTime(_birthday.Year, _birthday.Month, _birthday.Day);
        }

        public string Name
        {
            get { return name; }

            set { name = value; }

        }

        public string LastName
        {
            get { return lastName; }
            set { lastName = value; }
        }

        public System.DateTime Date
        {
            get { return birthday; }
            set
            {
                birthday = value;
            }
        }

        public override string ToString()
        {
            return name + " " + lastName + " " + birthday.ToString();
        }

        public override bool Equals(object obj)
        {
            if (this.GetType() != obj.GetType())
                return false;
            Person _person = (Person)obj;
            return (this.Name == _person.Name && this.LastName == _person.LastName && this.Date == _person.Date);
        }

        public static bool operator==(Person _per1, Person _per2)
        {
            return _per1.Name == _per2.Name && _per1.LastName == _per2.LastName && _per1.Date == _per2.Date;
        }

        public static bool operator!=(Person _per1, Person _per2)
        {
            return _per1.Name != _per2.Name || _per1.LastName != _per2.LastName || _per1.Date != _per2.Date;
        }

        public override int GetHashCode()
        {
            return Name.GetHashCode() + LastName.GetHashCode() + Date.GetHashCode();
        }

        public virtual object DeepCopy()
        { 
            return (object)(new Person(Name, LastName, new DateTime(Date.Year, Date.Month, Date.Day))); 
        }
    }
}
