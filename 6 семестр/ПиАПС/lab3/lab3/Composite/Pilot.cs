using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3.Composite
{
    internal class Pilot : Passenger
    {
        public Pilot() : base()
        {
            _baggageWeight = 0;
        }

        public override double GetWeight()
        {
            return _baggageWeight;
        }

        public override string Info()
        {
            return "Pilot";
        }
    }
}
