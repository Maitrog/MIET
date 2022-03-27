using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_6.Observer
{
    internal class Deanery : IObserver, ISubject
    {
        private readonly List<Department> _observers;
        private readonly List<Teacher> _teachers;
        private readonly List<Teacher> _teachersWhoDidReport;
        public List<Teacher> TeachersWhoDidNotReport { get; private set; }

        public Deanery()
        {
            _observers = new List<Department>();
            _teachers = new List<Teacher>();
            _teachersWhoDidReport= new List<Teacher>();
        }

        public void Attach(IObserver observer)
        {
            _observers.Add((Department)observer);
        }

        public void Detach(IObserver observer)
        {
            _observers?.Remove((Department)observer);
        }

        public void Notify()
        {
            TeachersWhoDidNotReport = _teachers.Except(_teachersWhoDidReport).ToList();
            foreach (Department department in _observers)
            {
                department.Update(this);
            }
        }

        public void Update(ISubject subject)
        {
            if(subject is Teacher teacher)
            {
                _teachersWhoDidReport.Add(teacher);
            }
        }

        public void AddTeacher(Teacher teacher)
        {
            _teachers.Add(teacher);
        }

        public void RemoveTeacher(Teacher teacher)
        {
            _teachers.Remove(teacher);
        }

        public void CheckTeachersReports()
        {
            Notify();
            TeachersWhoDidNotReport.Clear();
            _teachersWhoDidReport.Clear();
        }
    }
}
