namespace lab5.Interpreter
{
    internal class StatementExpression : AbstractExpression
    {
        private StatementExpression? _statement;
        private PrintExpression? _print;
        private ScanExpression? _scan;
        private AssignExpression? _assign;
        private ForExpression? _for;
        private IfExpression? _if;
        private ElseExpression? _else;

        public StatementExpression(StatementExpression? statement, PrintExpression print)
        {
            _statement = statement;
            _print = print;
        }

        public StatementExpression(StatementExpression? statement, ScanExpression scan)
        {
            _statement = statement;
            _scan = scan;
        }

        public StatementExpression(StatementExpression? statement, AssignExpression assign)
        {
            _statement = statement;
            _assign = assign;
        }

        public StatementExpression(StatementExpression? statement, ForExpression forExpression)
        {
            _statement = statement;
            _for = forExpression;
        }

        public StatementExpression(StatementExpression? statement, IfExpression ifExpression)
        {
            _statement = statement;
            _if = ifExpression;
        }

        public StatementExpression(StatementExpression? statement, IfExpression ifExpression, ElseExpression elseExpression)
        {
            _statement = statement;
            _if = ifExpression;
            _else = elseExpression;
        }
        public override object Interpret(Context context)
        {
            if (_print != null)
            {
                _print.Interpret(context);
                _statement?.Interpret(context);
            }
            else if (_scan != null)
            {
                _scan.Interpret(context);
                _statement?.Interpret(context);
            }
            else if (_assign != null)
            {
                _assign.Interpret(context);
                _statement?.Interpret(context);
            }
            else if (_for != null)
            {
                foreach (var _ in _for.Interpret(context))
                {
                    _statement?.Interpret(context);
                }
            }
            else if (_if != null)
            {
                if ((bool)_if.Interpret(context))
                {
                    _statement?.Interpret(context);
                }
                else if (_else != null)
                {
                    _else.Interpret(context);
                }
            }
            return context;
        }
    }
}