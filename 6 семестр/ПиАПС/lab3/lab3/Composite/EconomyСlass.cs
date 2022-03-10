using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3.Composite
{
    internal class EconomyСlass: Passenger
    {
        protected List<Passenger> _passengers;
        private readonly int _maxPassenger = 150;

        public EconomyСlass() : base()
        {
            _passengers = new();
        }
        public override void Add(Passenger passenger)
        {
            _passengers.Add(passenger);
        }
        public override void Remove(Passenger passenger)
        {
            _passengers.Remove(passenger);
        }
        public void RemoveMaxWeight()
        {
            var maxWeight = _passengers.Max( x => x._baggageWeight);
            var result = _passengers.First(x => x._baggageWeight == maxWeight);
            _passengers.Remove(result);
            Console.WriteLine($"Removed: {result.Info()}");
        }
        public override string Info()
        {
            int i = 0;
            string result = "EconomyСlass(";

            foreach (var p in _passengers)
            {
                result += p.Info();
                if (i != _passengers.Count - 1)
                {
                    result += "; ";
                }
                i++;
            }

            return result + ")";
        }

        public override double GetWeight()
        {
            double weight = 0;
            foreach (Passenger passenger in _passengers)
            {
                weight += passenger.GetWeight();
            }
            return weight;
        }

        public override bool IsReady()
        {
            return _passengers.Count == _maxPassenger;
        }
        public override bool IsCrew()
        {
            return false;
        }
    }
}
