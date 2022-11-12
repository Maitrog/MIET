namespace lab5.Interpreter
{
    internal class ScanExpression : AbstractExpression
    {
        private IdentifierExpression _identifier;
        public ScanExpression(IdentifierExpression identifier)
        {
            _identifier = identifier;
        }
        public override object Interpret(Context context)
        {
            var value = int.Parse(Console.ReadLine());
            AssignExpression assignExpression = new AssignExpression(_identifier,
                new ExpressionExpression(new TermExpression(new FactorExpression(new NumberExpression(value)))));
            return assignExpression.Interpret(context);
        }
    }
}
