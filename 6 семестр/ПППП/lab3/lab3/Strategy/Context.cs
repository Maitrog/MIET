using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3.Strategy
{
    internal class Context
    {
        private Strategy _strategy;

        public Strategy Strategy
        {
            set { _strategy = value; }
        }

        public Track ExecuteStrategy(int[] path, int volume)
        {
            return _strategy.Execute(path, volume);
        }

    }
}
