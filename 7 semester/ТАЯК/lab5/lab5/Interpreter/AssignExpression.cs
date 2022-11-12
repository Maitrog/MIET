using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5.Interpreter
{
    internal class AssignExpression : AbstractExpression
    {
        IdentifierExpression _identifier;
        ExpressionExpression _expression;

        public
        public override object Interpret(Context context)
        {
            throw new NotImplementedException();
        }
    }
}
