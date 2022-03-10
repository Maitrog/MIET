using System;
using System.Collections.Generic;
using System.Text;

namespace Lab5
{
    [Serializable]
    class Test
    {
        public Test(string _name, bool _credit)
        {
            Name = _name;
            Credit = _credit;
        }

        public Test()
        {
            Name = "";
            Credit = false;
        }
        public string Name { get; set; }
        public bool Credit { get; set; }

        public override string ToString()
        {
            return Name + ": " + Credit;
        }

        public object DeepCopy()
        {
            return new Test(Name, Credit);
        }
    }
}
