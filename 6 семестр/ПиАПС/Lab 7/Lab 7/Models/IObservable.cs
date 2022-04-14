using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal interface IObservable
    {
        void Attach(IObserver observer);

        void Detach(IObserver observer);

        void Notify();
    }
}
