using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal class EmptyCell : Cell
    {
        public EmptyCell() : base() { }
        public override CellState CreateCellState()
        {
            return new EmptyCellState();
        }
    }
}
