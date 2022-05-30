using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal class BombCell : Cell
    {
        public BombCell() : base() { }
        public override CellState CreateCellState()
        {
            return new BombCellState();
        }
    }
}
