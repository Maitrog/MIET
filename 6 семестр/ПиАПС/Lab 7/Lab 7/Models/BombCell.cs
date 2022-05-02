using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal class BombCell : BaseCell, IBomb
    {
        public BombCell()
        {
            Cells = new List<BaseCell>();
            IsBomb = true;
            IsMark = false;
            IsOpen = false;
        }
        public BaseCell GetBomb()
        {
            return this;
        }
    }
}
