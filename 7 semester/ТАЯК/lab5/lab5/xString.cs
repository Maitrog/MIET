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
    }
}
