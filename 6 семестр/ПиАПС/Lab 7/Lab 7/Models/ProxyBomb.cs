using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal class ProxyBomb : IBomb
    {
        private readonly BaseCellCreator _cellCreator;
        private BaseCell _realBombCell;

        public ProxyBomb()
        {
            _cellCreator = new BombCreator();
        }
        public BaseCell GetBomb()
        {
            if(_realBombCell == null)
            {
                _realBombCell = _cellCreator.CreateCell();
            }
            return ((BombCell)_realBombCell).GetBomb();
        }
    }
}
