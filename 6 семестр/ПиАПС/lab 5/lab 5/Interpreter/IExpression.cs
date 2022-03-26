using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_5.Interpreter
{
    internal interface IExpression
    {
        string Interpret(string expression);
    }
}
