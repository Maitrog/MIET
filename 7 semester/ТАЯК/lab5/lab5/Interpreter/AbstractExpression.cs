using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5.Interpreter
{
    abstract class AbstractExpression
    {
        public abstract object Interpret(Context context);
    }
}
