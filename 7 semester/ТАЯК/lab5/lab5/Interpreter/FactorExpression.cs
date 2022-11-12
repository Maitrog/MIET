using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5.Interpreter
{
    internal class FactorExpression : AbstractExpression
    {
        NumberExpression? _number;
        IdentifierExpression? _identifier;
        ExpressionExpression? _expression;

        public FactorExpression (NumberExpression number)
        {
            _number = number;
        }

        public FactorExpression(IdentifierExpression identifier)
        {
            _identifier = identifier;
        }

        public FactorExpression(ExpressionExpression expression)
        {
            _expression = expression;
        }
        public override object Interpret(Context context)
        {
            if(_number != null)
            {
                return _number.Interpret(context);
            }
            if(_identifier != null)
            {
                return _identifier.Interpret(context);
            }
            if(_expression != null)
            {
                return _expression.Interpret(context);
            }
            throw new Exception();
        }
    }
}
