using System;
using System.Collections.Generic;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;
using System.Text;

namespace Lab6
{
    [Serializable]
    class TimesList
    {
        private List<TimeItem> timeItems;
        public TimesList()
        {
            timeItems = new List<TimeItem>(0);
        }

        public void Add(TimeItem item)
        {
            timeItems.Add(item);
        }

        public bool Save(string filename)
        {
            BinaryFormatter binaryFormatter = new BinaryFormatter();
            try
            {
                using (FileStream stream = new FileStream(filename, FileMode.Open))
                {
                    binaryFormatter.Serialize(stream, this);
                    return true;
                }
            }
            catch
            {
                return false;
            }
        }
        public bool Load(string filename)
        {
            BinaryFormatter binaryFormatter = new BinaryFormatter();
            TimesList list;
            try
            {
                using (FileStream stream = new FileStream(filename, FileMode.Open))
                {
                    list = (TimesList)binaryFormatter.Deserialize(stream);
                    for (int i = 0; i < list.timeItems.Count; i++)
                    {
                        this.Add(list.timeItems[i]);
                    }

                    return true;
                }
            }
            catch
            {
                return false;
            }
        }

        public override string ToString()
        {
            string str = "";
            for (int i = 0; i < timeItems.Count; i++)
                str += timeItems[i].ToString();
            return str;
        }
    }
}
