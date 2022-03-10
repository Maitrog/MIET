using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_1.AbstractFactory
{
    internal class TaxiBoard : BoardAnyCar
    {
        public TaxiBoard (): base()
        {
            MaxPassengers = 4;
            BoardDriver( new TaxiDriver());
            for(int i = 0; i < MaxPassengers; i++)
            {
                BoardPassenger(new Passenger());
            }
        }

        public override string Info()
        {
            return "Taxi";
        }
    }
}
