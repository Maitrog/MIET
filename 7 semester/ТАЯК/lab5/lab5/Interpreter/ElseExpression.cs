namespace lab5.Interpreter
{
    internal class ElseExpression : AbstractExpression
    {
        private StatementExpression? _statement;

        public ElseExpression(StatementExpression statement)
        {
            _statement = statement;
        }

        public override object Interpret(Context context)
        {
            if (_statement != null)
            {
                _statement.Interpret(context);
            }
            return context;
        }
    }
}
