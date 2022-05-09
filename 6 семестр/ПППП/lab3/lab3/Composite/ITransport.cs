using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3.Composite
{
    internal interface ITransport
    {
        public void Add(ITransport transport);
        public int GetDistance();
        public void Remove(ITransport transport);
        public double SumCost(int mass, int dist);
        public double SumCost(int mass);
        public double SumTime(int dist);
        public double SumTime();

    }
}
