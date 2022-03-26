using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_5.Interpreter
{
    internal class TabulationExpression : IExpression
    {
        public string Interpret(string expression)
        {
            for (int i = 1; i < expression.Length; i++)
            {
                if (expression[i] == '\t' && expression[i - 1] == '\t' &&
                    (i == 1 || i > 3 && expression[i - 2] == '\n' && expression[i - 3] == '\r'))
                {
                    expression = expression.Remove(i, 1);
                    i--;
                }
                else if(expression[i] == '\t' && expression[i - 1] == '\n' && expression[i - 2] == '\r') { }
                else if (expression[i] == '\t')
                {
                    expression = expression.Remove(i, 1);
                    expression = expression.Insert(i, " ");
                }
            }
            return expression;
        }
    }
}
