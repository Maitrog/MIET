namespace lab5.Interpreter
{
    internal class NumberExpression : AbstractExpression
    {
        int _value;
        public NumberExpression(int value)
        {
            _value = value;
        }
        public override object Interpret(Context context)
        {
            return _value;
        }

        public override string ToString()
        {
            return _value.ToString();
        }
    }
}
