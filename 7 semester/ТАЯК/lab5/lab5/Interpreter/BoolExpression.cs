namespace lab5.Interpreter
{
    internal class BoolExpression : AbstractExpression
    {
        ExpressionExpression _leftExpression;
        ExpressionExpression _rightExpression;
        string _operation;

        public BoolExpression(ExpressionExpression leftExpression, ExpressionExpression rightExpression, string operation)
        {
            _leftExpression = leftExpression;
            _rightExpression = rightExpression;
            _operation = operation;
        }

        public override object Interpret(Context context)
        {
            return _operation switch
            {
                "<" => (int)_leftExpression.Interpret(context) < (int)_rightExpression.Interpret(context),
                ">" => (int)_leftExpression.Interpret(context) > (int)_rightExpression.Interpret(context),
                "==" => (int)_leftExpression.Interpret(context) == (int)_rightExpression.Interpret(context),
                "!=" => (int)_leftExpression.Interpret(context) != (int)_rightExpression.Interpret(context),
                _ => throw new Exception(),
            };
        }
    }
}
