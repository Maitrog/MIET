using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    internal class Car : ITransport
    {
        private double _price;
        private int _speed;
        private int _volume;
        private int _distance;

        public Car()
        {
            _price = 100;
            _speed = 60;
            _volume = 50;
            _distance = 0;
        }
        public Car(Tuple<double, int, int> tuple, int dist)
        {
            _price = tuple.Item1;
            _speed = tuple.Item2;
            _volume = tuple.Item3;
            _distance = dist;
        }
        public int GetDistance()
        {
            return _distance;
        }

        public double SumCost(int mass, int dist)
        {
            return (mass / _volume) * SumTime(dist) * _price;
        }

        public double SumTime(int dist)
        {
            return dist / _speed;
        }
    }
}
