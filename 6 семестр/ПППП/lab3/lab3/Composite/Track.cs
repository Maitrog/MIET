using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3.Composite
{
    internal class Track: ITransport
    {
        private double _cost;
        private double _time;
        private int _volume;
        public List<ITransport> Transport { get; init; }

        public Track()
        {
            _cost = 0;
            _time = 0;
            _volume = 0;
            Transport = new List<ITransport>();
        }
        public Track(ITransport[] transports, int volume)
        {
            _volume = volume;
            Transport = new List<ITransport>(transports);
            _cost = SumCost(volume);
            _time = SumTime();
        }
        public Track(int volume)
        {
            _volume = volume;
            Transport = new List<ITransport>();
            _cost = SumCost(volume);
            _time = SumTime();
        }

        public void Add(ITransport transport)
        {
            Transport.Add(transport);
            _cost = SumCost(_volume);
            _time = SumTime();
        }

        public double GetCost()
        {
            return _cost;
        }

        public int GetDistance()
        {
            int dist = 0;
            foreach (var item in Transport)
            {
                dist += item.GetDistance();
            }
            return dist;
        }

        public void Remove(ITransport transport)
        {
            Transport.Remove(transport);
            _cost = SumCost(_volume);
            _time = SumTime();
        }

        public double SumCost(int mass)
        {
            double cost = 0;
            foreach(var item in Transport)
            {
                cost += item.SumCost(mass, item.GetDistance());
            }
            return cost;
        }

        public double SumTime()
        {
            double time = 0;
            foreach (var item in Transport)
            {
                time += item.SumTime(item.GetDistance());
            }
            return time;
        }

        public double SumCost(int mass, int dist)
        {
            throw new NotImplementedException();
        }

        public double SumTime(int dist)
        {
            throw new NotImplementedException();
        }
    }
}
