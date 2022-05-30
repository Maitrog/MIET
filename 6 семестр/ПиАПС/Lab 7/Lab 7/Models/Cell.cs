using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal abstract class Cell : IObservable, IObserver
    {
        public CellState CellState { get; init; }

        public Cell()
        {
            CellState = CreateCellState();
        }

        public bool IsOpen
        {
            get
            {
                return CellState.IsOpen;
            }
        }

        public bool IsBomb
        {
            get
            {
                if (CellState is BombCellState)
                {
                    return true;
                }
                return false;
            }
        }
        public void Attach(IObserver observer)
        {
            CellState.Attach(observer);
        }

        public void Detach(IObserver observer)
        {
            CellState.Detach(observer);
        }

        public void Notify()
        {
            CellState.Notify();
        }

        public void Update(IObservable subject)
        {
            CellState.Update(subject);
        }
        public int Click()
        {
            return CellState.Click();
        }
        public bool RightClick()
        {
            return CellState.RightClick();
        }

        public abstract CellState CreateCellState();
    }
}
