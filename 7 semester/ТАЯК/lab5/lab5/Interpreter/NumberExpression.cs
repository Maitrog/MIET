using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5.Interpreter
{
    internal class NumberExpression : AbstractExpression
    {
        int _value;
        public NumberExpression(int value)
        {
            _value = value;
        }
        public override object Interpret(Context context)
        {
            return _value;
        }
    }
}
