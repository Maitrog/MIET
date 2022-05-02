using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3.Strategy
{
    internal class StrategySevenTransport : Strategy
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

            Train train1 = new();
            foreach (var item in _table)
            {
                if (item.Key.Contains(_points[path[1]]))
                {
                    train1 = new Train(_tableCost[item.Value * 3 + 1], _matrixDist[path[1], path[2]]);
                }
            }

            Car car2 = new();
            foreach (var item in _table)
            {
                if (item.Key.Contains(_points[path[2]]))
                {
                    car2 = new Car(_tableCost[item.Value * 3 + 2], _matrixDist[path[2], path[3]]);
                }
            }

            Plane plane1 = new();
            foreach (var item in _table)
            {
                if (item.Key.Contains(_points[path[3]]))
                {
                    plane1 = new Plane(_tableCost[item.Value * 3], _matrixDist[path[3], path[4]]);
                }
            }

            Car car3 = new();
            foreach (var item in _table)
            {
                if (item.Key.Contains(_points[path[4]]))
                {
                    car3 = new Car(_tableCost[item.Value * 3 + 2], _matrixDist[path[4], path[5]]);
                }
            }

            Train train2 = new();
            foreach (var item in _table)
            {
                if (item.Key.Contains(_points[path[5]]))
                {
                    train2 = new Train(_tableCost[item.Value * 3 + 1], _matrixDist[path[5], path[6]]);
                }
            }

            Car car4 = new();
            foreach (var item in _table)
            {
                if (item.Key.Contains(_points[path[6]]))
                {
                    car4 = new Car(_tableCost[item.Value * 3 + 2], _matrixDist[path[6], path[7]]);
                }
            }

            Track track = new Track(new ITransport[] { car1, car2, car3, car4, train1, train2, plane1 }, volume);

            return track;
        }
    }
}
