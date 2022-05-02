using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    internal class Track
    {
        private double _cost;
        private double _time;
        private int _volume;

        public Track()
        {
            _cost = 0;
            _time = 0;
            _volume = 0;
        }
        public Track(ITransport[] transports, int volume)
        {
            _cost = 0;
            _time = 0;
            foreach (var item in transports)
            {
                _cost += item.SumCost(volume, item.GetDistance());
                _time += item.SumTime(item.GetDistance());
            }
        }
        public double GetCost()
        {
            return _cost;
        }
    }
}
