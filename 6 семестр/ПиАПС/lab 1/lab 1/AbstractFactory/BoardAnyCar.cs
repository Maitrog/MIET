using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_1.AbstractFactory
{
    internal abstract class BoardAnyCar
    {
        private List<Passenger> _passengers = new();
        private Driver? _driver;
        private int _maxPassengers;

        public bool IsReady()
        {
            if(_driver == null)
            {
                return false;
            }
            if(_passengers == null ||  _passengers.Count != _maxPassengers)
            {
                return false;
            }
            return true;
        }

        public abstract string Info();

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

        protected internal Driver? Driver
        {
            get => _driver;
            set
            {
                if (value != null)
                {
                    _driver = value;
                }
            }
        }

        public int MaxPassengers
        {
            get => _maxPassengers;
            protected internal set { _maxPassengers = value; }
        }

        public virtual void BoardDriver(Driver driver)
        {
            Driver = driver;
        }

        public virtual void BoardPassenger(Passenger passenger)
        {
            if (Passengers.Count != MaxPassengers)
            {
                Passengers.Add(passenger);
            }
        }
    }
}
