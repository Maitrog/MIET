using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    internal interface ITransport
    {
        public int GetDistance();
        public double SumCost(int mass, int dist);
        public double SumTime(int dist);
    }
}
