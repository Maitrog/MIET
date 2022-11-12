namespace lab5.Interpreter
{
    internal class PrintExpression : AbstractExpression
    {
        private StringExpression? _string;
        private ExpressionExpression? _expression;
        private PrintExpression? _print;

        public PrintExpression(StringExpression identifier)
        {
            _string = identifier;
            _expression = null;
            _print = null;
        }

        public PrintExpression(ExpressionExpression expression)
        {
            _string = null;
            _expression = expression;
            _print = null;
        }

        public PrintExpression(StringExpression identifier, PrintExpression print)
        {
            _string = identifier;
            _expression = null;
            _print = print;
        }

        public PrintExpression(ExpressionExpression expression, PrintExpression print)
        {
            _string = null;
            _expression = expression;
            _print = print;
        }

        public override object Interpret(Context context)
        {
            if(_string != null)
            {
                Console.WriteLine(_string.Interpret(context));
            }
            else if(_expression != null)
            {
                Console.WriteLine(_expression.Interpret(context).ToString());
            }

            if(_print != null)
            {
                _print.Interpret(context);
            }
            return context;
        }
    }
}
