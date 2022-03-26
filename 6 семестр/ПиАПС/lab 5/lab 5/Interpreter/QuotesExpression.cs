using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_5.Interpreter
{
    internal class QuotesExpression : IExpression
    {
        public string Interpret(string expression)
        {
            bool isOpenQuote = true;
            for (int i = 0; i < expression.Length; i++)
            {
                if (expression[i] == '"')
                {
                    expression = expression.Remove(i, 1);
                    if (isOpenQuote)
                    {
                        expression = expression.Insert(i, "«");
                        isOpenQuote = false;
                    }
                    else
                    {
                        expression = expression.Insert(i, "»");
                        isOpenQuote = true;
                    }
                }
            }
            return expression;
        }
    }
}
