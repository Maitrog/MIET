using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab
{
    static internal class Expression
    {
        public static IEnumerable<TSource> Concat<TSource>(this IEnumerable<TSource> first, TSource second)
        {
            TSource[] result = new TSource[first.Count() + 1];
            for (int i = 0; i < first.Count(); i++)
            {
                result[i] = ((TSource[])first)[i];
            }
            result[first.Count()] = second;

            IEnumerable<TSource> r = result;
            return r;
        }
    }
}
