using lab3.Composite;
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
            Track track = new Track(volume);
            foreach (var item in Constants._table)
            {
                if (item.Key.Contains(Constants._points[path[0]]))
                {
                    Car car = new Car(Constants._tableCost[item.Value * 3 + 2], Constants._matrixDist[path[0], path[1]]);
                    track.Add(car);
                }
            }

            return track;
        }
    }
}
