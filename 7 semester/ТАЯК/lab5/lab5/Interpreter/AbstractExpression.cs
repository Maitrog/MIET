namespace lab5.Interpreter
{
    abstract class AbstractExpression
    {
        public abstract object Interpret(Context context);
    }
}
