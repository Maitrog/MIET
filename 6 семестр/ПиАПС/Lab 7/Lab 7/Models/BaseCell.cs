using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal abstract class BaseCell : IObservable, IObserver
    {
        private bool _isBomb;
        public List<BaseCell> Cells { get; init; }
        public bool IsBomb
        {
            get
            {
                return _isBomb;
            }
            protected set
            {
                _isBomb = value;
            }
        }
        public bool IsMark { get; set; }
        public bool IsOpen { get; protected set; }

        public void Attach(IObserver observer)
        {
            if (observer is BaseCell cell)
            {
                Cells.Add(cell);
            }
        }

        public void Detach(IObserver observer)
        {
            if (observer is BaseCell cell)
            {
                Cells.Remove(cell);
            }
        }

        public virtual int GetBombCount()
        {
            return -1;
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

        public void Open()
        {
            IsOpen = true;
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
    }
}
