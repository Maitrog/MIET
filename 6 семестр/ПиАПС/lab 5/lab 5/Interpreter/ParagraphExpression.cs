using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_5.Interpreter
{
    internal class ParagraphExpression : IExpression
    {
        public string Interpret(string expression)
        {
            for (int i = 3; i < expression.Length; i++)
            {
                if (expression[i] == '\n' && expression[i - 1] == '\r' &&
                    expression[i - 2] == '\n' && expression[i - 3] == '\r')
                {
                    expression = expression.Remove(i - 1, 2);
                    i -= 2;
                }
            }
            return expression;
        }
    }
}
