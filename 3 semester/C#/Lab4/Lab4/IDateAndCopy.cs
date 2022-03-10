using System;
using System.Collections.Generic;
using System.Text;

namespace Lab4
{
    interface IDateAndCopy
    {
        object DeepCopy();
        DateTime Date{ get; set; }
    }
}
