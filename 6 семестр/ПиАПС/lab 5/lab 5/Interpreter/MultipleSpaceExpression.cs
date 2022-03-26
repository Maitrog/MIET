using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_5.Interpreter
{
    internal class MultipleSpaceExpression : IExpression
    {
        public string Interpret(string expression)
        {
            for (int i = 1; i < expression.Length; i++)
            {
                if (expression[i] == ' ' && expression[i - 1] == ' ')
                {
                    expression = expression.Remove(i,1);
                    i--;
                }
            }
            return expression;
        }
    }
}
