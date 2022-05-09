using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal abstract class BaseCellCreator
    {
        public Cell CreateCell()
        {
            return new Cell() { CellState = CreateCellState() };
        }

        public abstract CellState CreateCellState();
    }
}
