using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_5.Interpreter
{
    internal class TextExpression : IExpression
    {
        private List<IExpression> _expressions;

        public TextExpression()
        {
            _expressions = new List<IExpression>()
            {
                new TabulationExpression(),
                new MultipleSpaceExpression(),
                new DashExpression(),
                new QuotesExpression(),
                new SpaceWithBracketExpression(),
                new ParagraphExpression()
            };
        }
        public string Interpret(string expression)
        {
            for(int i = 0; i < _expressions.Count; i++)
            {
                expression = _expressions[i].Interpret(expression);
            }
            return expression;
        }
    }
}
