using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace Lab5
{
    delegate T KeySelector<T>(Student st);
    delegate void StudentsChangedHandler<T>(object source, StudentsChangedEventArgs<T> args);
    class StudentCollection<TKey>
    {
        private Dictionary<TKey, Student> studentDict;
        private KeySelector<TKey> keySelector;
        public string CollectionName { get; set;}
        public event StudentsChangedHandler<TKey> StudentChenged;

        public StudentCollection(KeySelector<TKey> _keySelector)
        {
            keySelector = _keySelector;
            studentDict = new Dictionary<TKey, Student>();
        }

        public void AddStudents(params Student[] students)
        {
            for(int i = 0; i <students.Length; i++)
            {
                students[i].PropertyChanged += PropertiesChanged;
                studentDict.Add(keySelector(students[i]), students[i]);
                StudentChenged?.Invoke(this, new StudentsChangedEventArgs<TKey>(CollectionName, Action.Add, "", keySelector(students[i])));
            }
        }

        public override string ToString()
        {
            string str = "";
            foreach(var i in studentDict)
            {
                str += i.Value.ToString() + '\n';
            }
            return str;
        }

        public string ToShortString()
        {
            string str = "";
            foreach(var i in studentDict)
            {
                str += i.Value.Person.ToString() + " Education: " + i.Value.Education + " Group: " + i.Value.Group + 
                    " Exam: " + i.Value.ListExam.Count + " Test: " + i.Value.ListTest.Count + " Avg mark: " + i.Value.AvgMark() + '\n';
            }
            return str;
        }

        public double MaxAvgMark
        {
            get
            {
                return studentDict.Select(stud => stud.Value.AvgMark()).Max();
            }
        }

        public IEnumerable<KeyValuePair<TKey, Student>> EducationForm(Education value)
        {
            return studentDict.Where(stud => stud.Value.Education == value).Select(stud => stud);
        }

        public IEnumerable<IGrouping<Education, KeyValuePair<TKey, Student>>> GroupByEducation
        {
            get
            {
                return studentDict.GroupBy(stud => stud.Value.Education);
            }
        }

        public bool Remove(Student st)
        {
            if (studentDict.ContainsValue(st))
            {
                foreach (var i in studentDict)
                {
                    if (i.Value == st)
                    {
                        StudentChenged?.Invoke(this, new StudentsChangedEventArgs<TKey>(CollectionName, Action.Remove, "", i.Key));
                        i.Value.PropertyChanged -= PropertiesChanged;
                        studentDict.Remove(i.Key);
                        break;
                    }
                }
                return true;
            }
            return false;
        }

        public void PropertiesChanged(object sender, PropertyChangedEventArgs _propertyChanged)
        {
            StudentChenged?.Invoke(this, new StudentsChangedEventArgs<TKey>(CollectionName, Action.Property, _propertyChanged.PropertyName, keySelector((Student)sender)));
        }
    }
}
