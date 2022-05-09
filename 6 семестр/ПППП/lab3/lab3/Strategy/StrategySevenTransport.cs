using lab3.Composite;
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
            Track track = new Track(volume);
            foreach (var item in Constants._table)
            {
                if (item.Key.Contains(Constants._points[path[0]]))
                {
                    Car car = new Car(Constants._tableCost[item.Value * 3 + 2], Constants._matrixDist[path[0], path[1]]);
                    track.Add(car);
                }
            }

            foreach (var item in Constants._table)
            {
                if (item.Key.Contains(Constants._points[path[1]]))
                {
                    Train train = new Train(Constants._tableCost[item.Value * 3 + 1], Constants._matrixDist[path[1], path[2]]);
                    track.Add(train);
                }
            }

            foreach (var item in Constants._table)
            {
                if (item.Key.Contains(Constants._points[path[2]]))
                {
                    Car car = new Car(Constants._tableCost[item.Value * 3 + 2], Constants._matrixDist[path[2], path[3]]);
                    track.Add(car);
                }
            }

            foreach (var item in Constants._table)
            {
                if (item.Key.Contains(Constants._points[path[3]]))
                {
                    Plane plane = new Plane(Constants._tableCost[item.Value * 3], Constants._matrixDist[path[3], path[4]]);
                    track.Add(plane);
                }
            }

            foreach (var item in Constants._table)
            {
                if (item.Key.Contains(Constants._points[path[4]]))
                {
                    Car car = new Car(Constants._tableCost[item.Value * 3 + 2], Constants._matrixDist[path[4], path[5]]);
                    track.Add(car);
                }
            }

            foreach (var item in Constants._table)
            {
                if (item.Key.Contains(Constants._points[path[5]]))
                {
                    Train train = new Train(Constants._tableCost[item.Value * 3 + 1], Constants._matrixDist[path[5], path[6]]);
                    track.Add(train);
                }
            }

            foreach (var item in Constants._table)
            {
                if (item.Key.Contains(Constants._points[path[6]]))
                {
                    Car car = new Car(Constants._tableCost[item.Value * 3 + 2], Constants._matrixDist[path[6], path[7]]);
                    track.Add(car);
                }
            }

            return track;
        }
    }
}
