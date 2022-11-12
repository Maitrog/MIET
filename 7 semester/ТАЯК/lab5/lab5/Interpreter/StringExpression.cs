namespace lab5.Interpreter
{
    internal class StringExpression : AbstractExpression
    {
        private string _value;

        public StringExpression(string value)
        {
            _value = value;
        }

        public override object Interpret(Context context)
        {
            return _value;
        }
    }
}
