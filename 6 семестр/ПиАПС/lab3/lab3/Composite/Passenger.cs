using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3.Composite
{
    internal class Passenger
    {
        protected internal double _baggageWeight;
        protected internal double _maxWeight;

        public Passenger()
        {
            Random random = new();
            _baggageWeight = Math.Round(5.0 + random.NextDouble() * 55, 2);
            _maxWeight = 60;
        }
        public virtual string Info()
        {
            return $"Passenger: {_baggageWeight}kg";
        }

        public virtual double GetWeight()
        {
            return _baggageWeight;
        }

        public virtual bool IsReady()
        {
            return true;
        }

        public virtual bool IsCrew()
        {
            return true;
        }

        public virtual void Add(Passenger passenger)
        {
            throw new Exception();
        }
        public virtual void Remove(Passenger passenger)
        {
            throw new Exception();
        }
    }
}
