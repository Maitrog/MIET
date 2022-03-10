using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_1.AbstractFactory
{
    internal class TaxiDriver : Driver
    {
        public TaxiDriver() : base()
        {
            License = "B";
        }
    }
}
