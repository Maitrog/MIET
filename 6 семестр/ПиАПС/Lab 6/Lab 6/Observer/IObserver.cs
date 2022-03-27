using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_6.Observer
{
    internal interface IObserver
    {
        void Update(ISubject subject);
    }
}
