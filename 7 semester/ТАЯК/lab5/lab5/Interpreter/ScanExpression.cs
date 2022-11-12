namespace lab5.Interpreter
{
    internal class ScanExpression : AbstractExpression
    {
        private IdentifierExpression _identifier;
        public ScanExpression()
        {
        }
        public override object Interpret(Context context)
        {
            var name = Console.ReadLine();
            _identifier = new IdentifierExpression(name!);
            return _identifier.Interpret(context);
        }
    }
}
