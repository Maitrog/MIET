using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_2.Builder
{
    internal class TaxiBuilder : IBuilder
    {
        private readonly Board _board;
        public TaxiBuilder()
        {
            _board = new Board();
            _board.MaxPassengers = 4;
            _board.MaxDrivers = 1;
        }

        public void BuildDriver()
        {
            Reset();
        }

        public void BuildPassenger()
        {
            Random rd = new();
            for (int i = 0; i < _board.MaxPassengers; i++)
            {
                var types = new PassengerType[2] { PassengerType.ADULT, PassengerType.CHILD };
                _board.Passengers.Add(new Passenger() { Type = types[rd.Next(types.Length)], BaggageWeight = 0 });
            }
        }

        public void CheckProtected()
        {
            throw new NotImplementedException();
        }

        public Board GetBoard()
        {
            Board result = _board;
            Reset();
            return result;
        }

        public void Reset()
        {
            _board.BoardDriver(new Driver() { License = "B" });
        }
    }
}
