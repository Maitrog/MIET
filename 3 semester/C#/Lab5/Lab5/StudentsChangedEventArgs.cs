using System;
using System.Collections.Generic;
using System.Text;

namespace Lab5
{
    class StudentsChangedEventArgs<TKey>: System.EventArgs
    {
        public string CollectionName { get; set; }
        public Action Action { get; set; }
        public string PropertyName { get; set; }
        public TKey Key { get; set; }

        public StudentsChangedEventArgs(string _collection, Action _action, string _property, TKey _key)
        {
            CollectionName = _collection;
            Action = _action;
            PropertyName = _property;
            Key = _key;
        }

        public override string ToString()
        {
            return $"{CollectionName} {Action} {PropertyName} {Key}";
        }
    }
}
