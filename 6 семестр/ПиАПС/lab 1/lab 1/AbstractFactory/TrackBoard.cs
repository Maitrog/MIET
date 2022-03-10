using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_1.AbstractFactory
{
    internal class TrackBoard : BoardAnyCar
    {
        public TrackBoard(): base()
        {
            MaxPassengers = 10;
            BoardDriver(new TrackDriver());
            for (int i = 0; i < MaxPassengers; i++)
            {
                BoardPassenger(new Fridge());
            }
        }
        public override string Info()
        {
            return "Track";
        }

        public override void BoardPassenger(Passenger fridge)
        {
            base.BoardPassenger(fridge);
        }
    }
}
