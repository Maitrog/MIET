using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal interface IObserver
    {
        void Update(IObservable subject);
    }
}
