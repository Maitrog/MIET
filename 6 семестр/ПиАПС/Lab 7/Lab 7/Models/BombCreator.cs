using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal class BombCreator : BaseCellCreator
    {
        public override BaseCell CreateCell()
        {
            return new BombCell();
        }
    }
}
