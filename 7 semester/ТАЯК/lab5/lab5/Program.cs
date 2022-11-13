using lab5;
using lab5.Interpreter;

CBASInterpreter PushdownAutomaton = new CBASInterpreter(@"C:\Users\Mihay\Documents\MIET\7 semester\ТАЯК\ТАЯК\Laba5\test2.txt");

var program = File.ReadAllText("C:\\Users\\Mihay\\Documents\\MIET\\7 semester\\ТАЯК\\ТАЯК\\Laba5\\program.txt");
PushdownAutomaton.Interpret(program);