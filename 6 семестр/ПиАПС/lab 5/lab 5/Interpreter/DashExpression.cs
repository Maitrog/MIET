using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_5.Interpreter
{
    internal class DashExpression : IExpression
    {
        public string Interpret(string expression)
        {
            for(int i = 2; i < expression.Length; i++)
            {
                if(expression[i] == ' ' && expression[i - 1] == '-' && expression[i - 2] == ' ')
                {
                    expression = expression.Remove(i - 1,1);
                    expression = expression.Insert(i - 1, "—");
                }
            }
            return expression;
        }
    }
}
