using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal abstract class CellState : IObservable, IObserver
    {
        public List<Cell> Cells { get; init; }
        public bool IsMark { get; set; }
        public bool IsOpen { get; protected set; }

        public CellState()
        {
            Cells = new List<Cell>();
        }

        public void Attach(IObserver observer)
        {
            if (observer is Cell cell)
            {
                Cells.Add(cell);
            }
        }

        public void Detach(IObserver observer)
        {
            if (observer is Cell cell)
            {
                Cells.Remove(cell);
            }
        }

        public void Notify()
        {
            foreach (var cell in Cells)
            {
                if (GetBombCount() == 0)
                {
                    cell.Update(this);
                }
            }
        }

        public abstract void Update(IObservable subject);

        public void Open()
        {
            if (IsMark == false)
            {
                IsOpen = true;
            }
        }

        public bool RightClick()
        {
            if (IsOpen == false)
            {
                IsMark = !IsMark;
            }
            return IsMark;
        }

        public abstract int Click();
        public abstract int GetBombCount();
    }
}
