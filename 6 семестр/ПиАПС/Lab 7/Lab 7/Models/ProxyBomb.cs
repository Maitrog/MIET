using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal class ProxyBomb : IBomb
    {
        private BombCell _realBombCell;

        public Cell GetBomb()
        {
            if(_realBombCell == null)
            {
                _realBombCell = new BombCell();
            }
            return _realBombCell.GetBomb();
        }
    }
}
