using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_1.AbstractFactory
{
    internal class TrackDriver: Driver
    {
        public TrackDriver(): base()
        {
            _license = "C";
        }
    }
}
