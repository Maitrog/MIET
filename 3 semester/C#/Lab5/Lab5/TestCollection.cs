using System;
using System.Collections.Generic;
using System.Text;

namespace Lab5
{
    delegate KeyValuePair<K, V> GenerateElement<K, V>(int j);
    class TestCollection<TKey, TValue>
    {

        private List<TKey> tKeyList;
        private List<string> stringList;
        private Dictionary<TKey, TValue> tKeyDict;
        private Dictionary<string, TValue> stringDict;
        private GenerateElement<TKey, TValue> generateElement;

        public TestCollection(int _count, GenerateElement<TKey, TValue> _generateElement)
        {
            generateElement = _generateElement;
            tKeyList = new List<TKey>();
            stringList = new List<string>();
            tKeyDict = new Dictionary<TKey, TValue>();
            stringDict = new Dictionary<string, TValue>();
            for (int i = 0; i < _count; ++i)
            {
                tKeyList.Add(generateElement(i).Key);
                stringList.Add((generateElement(i).Key).ToString());
                tKeyDict.Add(generateElement(i).Key, generateElement(i).Value);
                stringDict.Add(generateElement(i).Key.ToString(), generateElement(i).Value);
            }
        }
        public List<TKey> TKeyList
        { get { return tKeyList; } }

        public List<string> StringList
        { get { return stringList; } }

        public Dictionary<TKey,TValue> TKeyDict
        { get { return tKeyDict; } }

        public Dictionary<string, TValue> StringDict
        { get { return stringDict; } }


    }
}
