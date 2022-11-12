using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
                return value;
            }
            else
            {
                context.Variable.Add(_name, 0);
                return 0;
            }
        }
    }
}
