using System;
using System.Collections.Generic;
using System.Text;

namespace lab2
{
    interface IDateAndCopy
    {
        object DeepCopy();
        DateTime Date{ get; set; }
    }
}
