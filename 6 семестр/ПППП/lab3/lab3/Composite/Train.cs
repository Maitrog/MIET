using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3.Composite
{
    internal class Train : ITransport
    {
        private double _price;
        private int _speed;
        private int _volume;
        private int _distance;

        public Train()
        {
            _price = 200;
            _speed = 100;
            _volume = 500;
            _distance = 0;
        }
        public Train(Tuple<double, int, int> tuple, int dist)
        {
            _price = tuple.Item1;
            _speed = tuple.Item2;
            _volume = tuple.Item3;
            _distance = dist;
        }

        public void Add(ITransport transport)
        {
            throw new NotImplementedException();
        }

        public int GetDistance()
        {
            return _distance;
        }

        public void Remove(ITransport transport)
        {
            throw new NotImplementedException();
        }

        public double SumCost(int mass, int dist)
        {
            return (mass / _volume) * SumTime(dist) * _price;
        }

        public double SumCost(int mass)
        {
            throw new NotImplementedException();
        }

        public double SumTime(int dist)
        {
            return dist / _speed;
        }

        public double SumTime()
        {
            throw new NotImplementedException();
        }
    }
}
