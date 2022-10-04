using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab
{
    internal class Crochemore
    {
        private string _str;
        private List<Dictionary<string, List<int>>> _substrings;

        public Crochemore(byte[] data, int minLength)
        {
            string inputStr = ConvertBytesToString(data);
            Initial(inputStr, minLength);
        }
        public Crochemore(string inputStr, int minLength)
        {
            Initial(inputStr, minLength);
        }
        public List<Dictionary<string, List<int>>> Substrings
        {
            get
            {
                return _substrings;
            }
        }
        public string ByteString
        {
            get
            {
                return _str;
            }
        }

        private void Initial(string inputStr, int minLength)
        {
            _str = inputStr;
            _substrings = new List<Dictionary<string, List<int>>>
            {
                new Dictionary<string, List<int>>()
            };

            for (int i = 0; i < _str.Length - 1; i += 2)
            {
                string item = _str[i..(i + 2)];
                if (_substrings[0].TryGetValue(item.ToString(), out List<int> indexes))
                {
                    indexes.Add(i);
                }
                else
                {
                    indexes = new List<int> { i };
                    _substrings[0].Add(item.ToString(), indexes);
                }
            }
            FindSubstring(minLength);
        }

        private void FindSubstring(int minLength)
        {
            for (int i = 0; i < _substrings.Count; i++)
            {
                var currentLevel = _substrings[i];
                Dictionary<string, List<int>> newLevel = new Dictionary<string, List<int>>();
                foreach (var item in currentLevel.Keys)
                {
                    if (item[^2] != 'F' && item[^1] != 'F')
                    {
                        foreach (var value in currentLevel[item])
                        {
                            int startIndex = value + item.Length;
                            var newSubstring = item + _str[startIndex..(startIndex + 2)];
                            if (newLevel.TryGetValue(newSubstring, out List<int> indexes))
                            {
                                if (indexes.Last() + newSubstring.Length < value)
                                {
                                    indexes.Add(value);
                                }
                            }
                            else
                            {
                                indexes = new List<int> { value };
                                newLevel.Add(newSubstring, indexes);
                            }
                        }
                    }
                }
                foreach (var item in newLevel)
                {
                    if (item.Value.Count == 1)
                    {
                        newLevel.Remove(item.Key);
                    }
                }
                if (newLevel.Count != 0)
                {
                    _substrings.Add(newLevel);
                }
            }

            for (int i = 0; i < _substrings.Count; i++)
            {
                Dictionary<string, List<int>> item = _substrings[i];
                if (item.Keys.First().Length < minLength * 2)
                {
                    _substrings.Remove(item);
                    i--;
                }
            }
        }

        private string ConvertBytesToString(byte[] data)
        {
            StringBuilder stringBuilder = new StringBuilder(data.Length * 2);
            foreach (var item in data)
            {
                stringBuilder.Append(item.ToString("X2"));
            }
            return stringBuilder.ToString();
        }
    }
}
