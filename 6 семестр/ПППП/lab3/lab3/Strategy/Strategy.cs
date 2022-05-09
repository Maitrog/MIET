using lab3.Composite;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3.Strategy
{
    internal abstract class Strategy
    {
        public abstract Track Execute(int[] path, int volume);
    }
}
