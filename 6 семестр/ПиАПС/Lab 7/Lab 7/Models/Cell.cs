using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal class Cell : IObservable, IObserver
    {
        public List<Cell> Cells { get; set; } = new List<Cell>();
        public bool IsBomb { get; set; } = false;
        public bool IsMark { get; set; } = false;
        public bool IsOpen { get; private set; } = false;
        public int GetBombCount()
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
        public void Open()
        {
            IsOpen = true;
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

        public void Update(IObservable subject)
        {
            if (IsOpen == false)
            {
                Open();
                if (GetBombCount() == 0)
                {
                    Notify();
                }
            }
        }

        public void Click()
        {
            Open();
            Notify();
        }

        public void Clear()
        {
            IsOpen = false;
            IsBomb = false;
            IsMark = false;
            Cells.Clear();
        }
    }
}
