using lab5;
using lab5.Interpreter;
//Context context = new Context();

//IdentifierExpression _identifier = new IdentifierExpression("a");
//IdentifierExpression b = new IdentifierExpression("b");
//ExpressionExpression _expressionFrom = new ExpressionExpression(new TermExpression(new FactorExpression(new NumberExpression(1))));
//ExpressionExpression _expressionTo = new ExpressionExpression(new TermExpression(new FactorExpression(new NumberExpression(101))));

//ForExpression _for = new ForExpression(_identifier, _expressionFrom, _expressionTo);

//AssignExpression assign = new AssignExpression(b,
//    new ExpressionExpression(new TermExpression(new FactorExpression(_identifier)),
//    new ExpressionExpression(new TermExpression(new FactorExpression(b))), '+'));

//PrintExpression print = new PrintExpression(new ExpressionExpression(new TermExpression(new FactorExpression(b))));

//StatementExpression statement1 = new StatementExpression(new StatementExpression(new StatementExpression(null, print), assign), _for);
//ProgramExpression programExpression = new ProgramExpression(statement1);

//programExpression.Interpret(context);

CBASInterpreter PushdownAutomaton = new CBASInterpreter(@"C:\Users\Mihay\Documents\MIET\7 semester\ТАЯК\ТАЯК\Laba5\test2.txt");

var program = File.ReadAllText("C:\\Users\\Mihay\\Documents\\MIET\\7 semester\\ТАЯК\\ТАЯК\\Laba5\\program.txt");
PushdownAutomaton.Interpret(program);