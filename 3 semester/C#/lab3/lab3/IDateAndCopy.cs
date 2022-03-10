using System;
using System.Collections.Generic;
using System.Text;

namespace lab3
{
    interface IDateAndCopy
    {
        object DeepCopy();
        DateTime Date{ get; set; }
    }
}
