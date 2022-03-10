using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_1.AbstractFactory
{
    internal class BusBoard : BoardAnyCar
    {
        public BusBoard(): base()
        {
            MaxPassengers = 30;
            BoardDriver( new BusDriver());
            for (int i = 0; i < MaxPassengers; i++)
            {
                BoardPassenger(new Passenger());
            }
        }

        public override string Info()
        {
            return "Bus";
        }
    }
}
