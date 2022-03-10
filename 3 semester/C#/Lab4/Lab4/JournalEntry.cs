using System;
using System.Collections.Generic;
using System.Text;

namespace Lab4
{
    class JournalEntry
    {
        public string CollectonName { get; set; }
        public Action Action { get; set; }
        public string PropertyName { get; set; }
        public string Key { get; set; }

        public JournalEntry(string _collectionName, Action _action, string _propertyName, string _key)
        {
            CollectonName = _collectionName;
            Action = _action;
            PropertyName = _propertyName;
            Key = _key;
        }

        public override string ToString()
        {
            return $"{CollectonName} {Action} {PropertyName} {Key}";
        }
    }
}
