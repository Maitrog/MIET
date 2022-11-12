namespace lab5.Interpreter
{
    internal class ProgramExpression : AbstractExpression
    {
        private StatementExpression _statement;

        public ProgramExpression(StatementExpression statement)
        {
            _statement = statement;
        }

        public override object Interpret(Context context)
        {
            return _statement.Interpret(context);
        }
    }
}
