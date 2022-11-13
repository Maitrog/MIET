using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5
{
    public static class xString
    {
        public static bool IsSpace(this string str)
        {
            foreach (var item in str)
            {
                if (!char.IsWhiteSpace(item))
                {
                    return false;
                }
            }
            return true;
        }

        public static bool IsEqualsBracketCount(this string str)
        {
            int open = 0;
            int close = 0;
            for(int i = 0; i < str.Length; i++)
            {
                if(str[i] == '(')
                {
                    open++;
                }
                if (str[i] == ')')
                {
                    close++;
                }
            }
            return open == close;
        }
    }
}
