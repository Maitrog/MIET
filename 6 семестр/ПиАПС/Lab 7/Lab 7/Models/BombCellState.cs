using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal class BombCellState : CellState
    {
        public override int Click()
        {
            if (IsMark)
            {
                return -2;
            }
            return GetBombCount();
        }

        public override int GetBombCount()
        {
            return -1;
        }

        public override void Update(IObservable subject)
        {
        }
    }
}
