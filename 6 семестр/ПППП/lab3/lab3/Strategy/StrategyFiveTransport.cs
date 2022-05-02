using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3.Strategy
{
    internal class StrategyFiveTransport : Strategy
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
            Plane plane1 = new();

            foreach (var item in _table)
            {
                if (item.Key.Contains(_points[path[1]]) && _points[path[1]].Contains("TS"))
                {
                    train1 = new Train(_tableCost[item.Value * 3 + 1], _matrixDist[path[1], path[2]]);
                }
                if (item.Key.Contains(_points[path[1]]) && _points[path[1]].Contains("AP"))
                {
                    plane1 = new Plane(_tableCost[item.Value * 3], _matrixDist[path[1], path[2]]);
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

            foreach (var item in _table)
            {
                if (item.Key.Contains(_points[path[3]]) && _points[path[3]].Contains("AP"))
                {
                    plane1 = new Plane(_tableCost[item.Value * 3], _matrixDist[path[3], path[4]]);
                }
                if (item.Key.Contains(_points[path[3]]) && _points[path[3]].Contains("TS"))
                {
                    train1 = new Train(_tableCost[item.Value * 3 + 1], _matrixDist[path[3], path[4]]);
                }
            }

            Car car3 = new();
            foreach (var item in _table)
            {
                if (item.Key.Contains(_points[path[4]]))
                {
                    car2 = new Car(_tableCost[item.Value * 3 + 2], _matrixDist[path[4], path[5]]);
                }
            }

            Track track = new Track(new ITransport[] { car1, car2, car3, train1, plane1 }, volume);
            return track;
        }
    }
}
