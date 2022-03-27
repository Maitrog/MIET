using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_6.Observer
{
    internal class Teacher: ISubject
    {
        public string Name { get; private set; }
        private readonly List<Deanery> _deaneries;

        public Teacher(string name)
        {
            Name = name;
            _deaneries = new List<Deanery>();
        }

        public void Attach(IObserver observer)
        {
            if(observer is Deanery deanery)
            {
                _deaneries.Add(deanery);
                deanery.AddTeacher(this);
            }
        }

        public void Detach(IObserver observer)
        {
            if( observer is Deanery deanery)
            {
                _deaneries.Remove(deanery);
                deanery.RemoveTeacher(this);
            }
        }

        public void Notify()
        {
            foreach(Deanery deanery in _deaneries)
            {
                deanery.Update(this);
            }
        }

        public void CreateReport()
        {
            Console.WriteLine(Name + " сделал отчет.");
            Notify();
        }
    }
}
