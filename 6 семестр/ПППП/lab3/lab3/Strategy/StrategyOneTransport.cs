using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3.Strategy
{
    internal class StrategyOneTransport : Strategy
    {
        public override Track Execute(int[] path, int volume)
        {
            
            Car car1 = new();
            foreach (var item in _table)
            {
                if (item.Key.Contains(_points[path[0]]))
                {
                    car1 = new Car(_tableCost[item.Value * 3 + 2], _matrixDist[path[0], path[1]]);
                }
            }

            Track track = new Track(new ITransport[] { car1 }, volume);
            return track;
        }
    }
}
