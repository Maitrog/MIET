using System;
using System.Collections.Generic;
using System.Text;

namespace Lab4
{
    class Journal
    {
        List<JournalEntry> journalEntries;

        public Journal()
        {
            journalEntries = new List<JournalEntry>();
        }
        public void StudentsChanged(object obj, StudentsChangedEventArgs<string> _args)
        {
            journalEntries.Add(new JournalEntry(_args.CollectionName, _args.Action, _args.PropertyName, _args.Key));
        }

        public override string ToString()
        {
            string str = "";
            foreach (var i in journalEntries)
                str += i.ToString() + "\n";
            return str;
        }

    }
}
