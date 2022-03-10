using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_2.Builder
{
    internal class Passenger
    {
        private PassengerType _type;
        private int _baggageWeight;

        public int BaggageWeight
        {
            get { return _baggageWeight; }
            set { _baggageWeight = value; }
        }

        public PassengerType Type
        {
            get { return _type; }
            set { _type = value; }
        }

        public override string ToString()
        {
            return _type.ToString() + ": " + _baggageWeight;
        }

    }

    internal enum PassengerType
    {
        ADULT,
        BENEFICIARY,
        CHILD
    }
}
