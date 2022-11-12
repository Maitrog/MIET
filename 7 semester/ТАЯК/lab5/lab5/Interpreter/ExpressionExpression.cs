using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5.Interpreter
{
    internal class ExpressionExpression : AbstractExpression
    {
        private TermExpression _term;
        private ExpressionExpression? _expression;
        private char? _operation;

        public ExpressionExpression(TermExpression term)
        {
            _term = term;
            _expression = null;
            _operation = null;
        }

        public ExpressionExpression(TermExpression term, ExpressionExpression expression, char opeartion)
        {
            _term = term;
            _expression = expression;
            _operation = opeartion;
        }
        public override object Interpret(Context context)
        {
            if (_operation != null && _expression != null)
            {
                switch (_operation)
                {
                    case '+': return (int)_term.Interpret(context) + (int)_expression.Interpret(context);
                    case '-': return (int)_term.Interpret(context) - (int)_expression.Interpret(context);
                }
            }
            return _term.Interpret(context);
        }
    }
}
