namespace lab5.Interpreter
{
    internal class TermExpression : AbstractExpression
    {
        FactorExpression _factor;
        TermExpression? _term;
        char? _operation;

        public TermExpression(FactorExpression factor)
        {
            _factor = factor;
            _term = null;
            _operation = null;
        }

        public TermExpression(FactorExpression factor, TermExpression term, char operation)
        {
            _factor = factor;
            _term = term;
            _operation = operation;
        }

        public override object Interpret(Context context)
        {
            if (_operation != null && _term != null)
            {
                switch (_operation)
                {
                    case '*': return (int)_factor.Interpret(context) + (int)_term.Interpret(context);
                    case '/': return (int)_factor.Interpret(context) - (int)_term.Interpret(context);
                }
            }
            return _factor.Interpret(context);
        }
    }
}
