using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal class Cell : BaseCell
    {
        public Cell()
        {
            Cells = new List<BaseCell>();
            IsBomb = false;
            IsMark = false;
            IsOpen = false;
        }
        public override int GetBombCount()
        {
            int count = 0;
            foreach (var cell in Cells)
            {
                if (cell.IsBomb)
                {
                    count++;
                }
            }
            return count;
        }
    }
}
