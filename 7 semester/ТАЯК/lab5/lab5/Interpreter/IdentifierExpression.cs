namespace lab5.Interpreter
{
    internal class IdentifierExpression : AbstractExpression
    {
        private string _name;

        public IdentifierExpression(string name)
        {
            _name = name;
        }

        public override object Interpret(Context context)
        {
            // return global variable
            if(context.Variable.TryGetValue(_name, out var value))
            {
                return new KeyValuePair<string, int>(_name, value);
            }
            else
            {
                context.Variable.Add(_name, 0);
                return new KeyValuePair<string, int>(_name, 0);
            }
        }
    }
}
