using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3.Composite
{
    internal class Airplane
    {
        protected internal List<Passenger> _passengers;
        public double MaxWeight { get; private set; }
        public Airplane()
        {
            _passengers = new();
            MaxWeight = 5000;
        }
        public Airplane(double maxWeight)
        {
            _passengers = new();
            MaxWeight = maxWeight;
        }

        public void Add(Passenger passenger)
        {
            _passengers.Add(passenger);
        }

        public void AddPassenger(Passenger passenger1, Passenger passenger2)
        {
            if (!passenger1.IsCrew())
            {
                passenger1.Add(passenger2);
            }
        }
        public string Info()
        {
            string result = "";
            foreach (Passenger passenger in _passengers)
            {
                result += passenger.Info() + "\n";
            }
            return result;
        }

        public double GetWeight()
        {
            double weight = 0;
            foreach (Passenger passenger in _passengers)
            {
                weight += passenger.GetWeight();
            }
            return weight;
        }

        public void RemoveBaggage()
        {
            EconomyСlass economyСlass = new();
            foreach (var p in _passengers)
            {
                if (p.GetType() == Type.GetType("lab3.Composite.EconomyСlass"))
                {
                    economyСlass = p as EconomyСlass;
                    break;
                }
            }
            while (GetWeight() > MaxWeight)
            {
                economyСlass.RemoveMaxWeight();
            }
        }
    }
}
