namespace lab5.Interpreter
{
    internal class ForExpression : AbstractExpression
    {
        private IdentifierExpression _identifier;
        private ExpressionExpression _expressionFrom;
        private ExpressionExpression _expressionTo;

        public ForExpression(IdentifierExpression identifier, ExpressionExpression expressionFrom, ExpressionExpression expressionTo)
        {
            _identifier = identifier;
            _expressionFrom = expressionFrom;
            _expressionTo = expressionTo;
        }

        public override IEnumerable<object> Interpret(Context context)
        {
            AssignExpression assign = new AssignExpression(_identifier, _expressionFrom);
            var i = ((KeyValuePair<string, int>)assign.Interpret(context)).Value;
            var to = (int)_expressionTo.Interpret(context);
            for (; i < to; i++)
            {
                assign = new AssignExpression(_identifier, new ExpressionExpression(new TermExpression(new FactorExpression(new NumberExpression(i)))));
                var a = assign.Interpret(context);
                yield return true;
            }
            yield break;
        }
    }
}
