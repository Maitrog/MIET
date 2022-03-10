using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_2.Builder
{
    internal class IntercityBusBuilder : IBuilder
    {
        private readonly Board _board;
        public IntercityBusBuilder()
        {
            _board = new Board();
            _board.MaxPassengers = 30;
            _board.MaxDrivers = 2;
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
                var types = new PassengerType[3] { PassengerType.ADULT, PassengerType.BENEFICIARY, PassengerType.CHILD };
                _board.Passengers.Add(new Passenger() { Type = types[rd.Next(types.Length)], BaggageWeight = rd.Next(0,20) });
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
            _board.BoardDriver(new Driver() { License = "D" });
            _board.BoardDriver(new Driver() { License = "D" });
        }
    }
}
