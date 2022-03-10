using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_2.Builder
{
    internal class Board
    {
        private List<Passenger> _passengers = new List<Passenger>();
        private List<Driver> _drivers = new List<Driver>();
        private int _maxPassengers;
        private int _maxDrivers;

        public bool IsReady()
        {
            if (_drivers == null)
            {
                return false;
            }
            if (_passengers != null && _passengers.Count == 0)
            {
                return false;
            }
            return true;
        }

        protected internal List<Passenger> Passengers
        {
            get => _passengers;
            set
            {
                if (value != null)
                {
                    _passengers = value;
                }
            }
        }

        protected internal List<Driver> Drivers
        {
            get => _drivers;
            set
            {
                if (value != null)
                {
                    _drivers = value;
                }
            }
        }

        public int MaxPassengers
        {
            get => _maxPassengers;
            protected internal set { _maxPassengers = value; }
        }
        public int MaxDrivers
        {
            get => _maxDrivers;
            protected internal set { _maxDrivers = value; }
        }
        public void BoardDriver(Driver driver)
        {
            if(_drivers.Count < _maxDrivers)
            {
                _drivers.Add(driver);
            }
        }

        public void BoardPassenger(Passenger passenger)
        {
            if (Passengers.Count != MaxPassengers)
            {
                Passengers.Add(passenger);
            }
        }
    }
}
