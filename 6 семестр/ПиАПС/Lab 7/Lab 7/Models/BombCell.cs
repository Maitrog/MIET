using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal class BombCell : IBomb
    {
        public Cell GetBomb()
        {
            return new Cell() { IsBomb = true };
        }
    }
}
