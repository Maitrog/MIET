using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace lab_2
{
    internal sealed class RSA44
    {
        private static readonly List<char> _defChar = new()
        {
            'А',
            'Б',
            'В',
            'Г',
            'Д',
            'Е',
            'Ё',
            'Ж',
            'З',
            'И',
            'Й',
            'К',
            'Л',
            'М',
            'Н',
            'О',
            'П',
            'Р',
            'С',
            'Т',
            'У',
            'Ф',
            'Х',
            'Ц',
            'Ч',
            'Ш',
            'Щ',
            'Ъ',
            'Ы',
            'Ь',
            'Э',
            'Ю',
            'Я',
            ' ',
            '0',
            '1',
            '2',
            '3',
            '4',
            '5',
            '6',
            '7',
            '8',
            '9'
        };
        private static readonly List<int> _primeNumber = new()
        {
            7,
            11,
            13,
            17,
            19,
            23,
            29,
            31,
            37,
            41,
            43,
            47,
            53,
            59,
            61,
            67,
            71,
            73,
            79,
            83,
            89,
            97,
            101,
            103,
            107,
            109,
            113,
            127,
            131,
            137,
            139,
            149,
            151,
            157,
            163,
            167,
            173,
            179,
            181,
            191,
            193,
            197,
            199
        };

        private readonly int _n;
        private readonly int _phi;
        private readonly int _d;
        private readonly int _e;

        public RSA44()
        {
            Random rnd = new();
            int p = _primeNumber[rnd.Next(0, _primeNumber.Count)];
            int q = _primeNumber[rnd.Next(0, _primeNumber.Count)];

            _n = p * q;
            _phi = (p - 1) * (q - 1);
            List<int> coprimes = GetCoprimes();
            _e = coprimes[rnd.Next(0, coprimes.Count)];
            _d = GetD();
        }
        public List<int> Encode(string str)
        {
            List<int> encodeStr = new();
            str = str.ToUpper();
            foreach (char c in str)
            {
                int index = _defChar.IndexOf(c) + 1;
                int newIndex = (int)BigInteger.ModPow(index, _e, _n);
                encodeStr.Add(newIndex);
            }
            return encodeStr;
        }

        public string Decode(List<int> encodeStr)
        {
            string decodeStr = "";
            foreach (int index in encodeStr)
            {
                int newIndex = (int)BigInteger.ModPow(index, _d, _n);
                decodeStr += _defChar[newIndex - 1];
            }
            return decodeStr;
        }

        public static string Decode(List<int> encodeStr, KeyValuePair<int, int> keyValuePair)
        {
            string decodeStr = "";
            foreach (int index in encodeStr)
            {
                int newIndex = (int)BigInteger.ModPow(index, keyValuePair.Key, keyValuePair.Value);
                decodeStr += _defChar[newIndex - 1];
            }
            return decodeStr;
        }

        public KeyValuePair<int, int> GetOpenKey() { return new KeyValuePair<int, int>(_e, _n); }
        public KeyValuePair<int, int> GetCloseKey() { return new KeyValuePair<int, int>(_d, _n); }

        private static int GCD(int a, int b)
        {
            return b > 0 ? GCD(b, a % b) : a;
        }

        private List<int> GetCoprimes()
        {
            List<int> coprimes = new(_phi);
            for (int i = 0; i < _n; i++)
            {
                if (GCD(_phi, i) == 1)
                {
                    coprimes.Add(i);
                }
            }
            return coprimes;
        }

        private int GetD()
        {
            int d;
            for (int i = 1; true; i++)
            {
                double dd = ((double)i * _phi + 1) / _e;
                if (dd == 0)
                {
                    continue;
                }
                d = (int)dd;
                if (d == dd)
                {
                    break;
                }
            }
            return d;
        }
    }
}
