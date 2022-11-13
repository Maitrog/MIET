using lab5.Interpreter;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Net.WebSockets;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace lab5
{
    internal class CBASInterpreter
    {
        readonly HashSet<string> P;
        readonly HashSet<string> Z;
        readonly Dictionary<string, HashSet<string>> FirstSet;
        readonly Dictionary<string, HashSet<string>> FollowSet;
        readonly Dictionary<int, HashSet<string>> PredictSet;
        readonly HashSet<string> Left;
        HashSet<TransitionFunction> _rules;
        readonly Dictionary<string, Dictionary<string, List<string>>> NormalPredictSet;

        public HashSet<TransitionFunction> Sigma { get; }

        public CBASInterpreter()
        {
            P = new HashSet<string>();
            Z = new HashSet<string>();
            FirstSet = new Dictionary<string, HashSet<string>>();
            FollowSet = new Dictionary<string, HashSet<string>>();
            PredictSet = new Dictionary<int, HashSet<string>>();
            Sigma = new HashSet<TransitionFunction>();
            Left = new HashSet<string>();
            NormalPredictSet = new Dictionary<string, Dictionary<string, List<string>>>();
        }

        public CBASInterpreter(string file)
        {
            P = new HashSet<string>();
            Z = new HashSet<string>();
            FirstSet = new Dictionary<string, HashSet<string>>();
            FollowSet = new Dictionary<string, HashSet<string>>();
            PredictSet = new Dictionary<int, HashSet<string>>();
            Sigma = new HashSet<TransitionFunction>();
            Left = new HashSet<string>();
            NormalPredictSet = new Dictionary<string, Dictionary<string, List<string>>>();

            var rulesText = File.ReadAllLines(file);
            foreach (var rule in rulesText)
            {
                TransitionFunction.TryParse(rule, out var transitionFunctions);
                AddRangeTransitionFunction(transitionFunctions);
            }

            InitFirstFollowSets();
            CreateFirstSets();
            CreateFollowSets();
            CreatePredictSets();
            if (NormalPredictSet.Count == 0)
            {
                CreateNormalPredictSets();
            }
        }

        public void AddRangeTransitionFunction(IEnumerable<TransitionFunction> transitionFunctions)
        {
            foreach (var transitionFunction in transitionFunctions)
            {
                Sigma.Add(transitionFunction);

                foreach (var item2 in transitionFunction.Action)
                {
                    Z.Add(item2);
                    if (item2 != "`")
                    {
                        Left.Add(transitionFunction.SymbolFromH);
                    }
                }

                P.Add(transitionFunction.SymbolFromH);
            }
        }

        public int FindError(string inputStr)
        {
            int errorCount = 0;
            Stack<string> memory = new Stack<string>();
            memory.Push("$");
            memory.Push("¬¬program");

            for (int i = 0; i < inputStr.Length; i++)
            {
                string item = GetNextItem(inputStr, i);
                while (item.IsSpace())
                {
                    i += item.Length;
                    item = GetNextItem(inputStr, i);
                }

                if (item.Length > 1)
                {
                    item = item.Trim();
                }

                if (memory.TryPop(out string c) && c != "$")
                {
                    bool isNonterminal = IsNonterminal(c);
                    if (!isNonterminal && c != item || isNonterminal && (!NormalPredictSet[c].ContainsKey(item) || NormalPredictSet[c][item] == null))
                    {
                        do
                        {
                            if (isNonterminal)
                            {
                                Console.WriteLine($"Error! Index: {i}. Symbol: '{item}'.");
                                errorCount++;
                            }
                            else if (item != "$")
                            {
                                Console.WriteLine($"Error! Index: {i}. Symbol: '{c}'.");
                                errorCount++;
                            }
                            i += item.Length;
                            item = GetNextItem(inputStr, i);
                        } while (isNonterminal && (!FirstSet[c].Contains(item) || FollowSet[c].Contains(item)));
                    }

                    if (c == item)
                    {
                        i += item.Length - 1;
                    }
                    else
                    {
                        i--;
                        if (isNonterminal && !string.IsNullOrEmpty(item))
                        {
                            foreach (var action in NormalPredictSet[c][item])
                            {
                                if (action != "~")
                                {
                                    memory.Push(action);
                                }
                            }
                        }
                    }
                }
            }

            return errorCount;
        }
        public void Interpret(string programText)
        {
            int i = 0;
            Context context = new Context();
            var program = new ProgramExpression(ParseStatement(programText, ref i));

            program.Interpret(context);
        }

        public StatementExpression ParseStatement(string programText, ref int i)
        {
            StatementExpression? returnStatement = null;
            bool isChangeBrackets = false;
            Stack<string> brackets = new Stack<string>();
            Stack<AbstractExpression> expressions = new Stack<AbstractExpression>();
            StatementExpression? lastStatement;
            var keywords = GetKeywords();
            for (; i < programText.Length;)
            {
                string item = GetNextItemWithoutSpace(programText, ref i);
                if (item == "{")
                {
                    brackets.Push(item);
                    isChangeBrackets = true;
                }

                if (item == "}")
                {
                    brackets.Pop();
                }

                if (isChangeBrackets && brackets.Count == 0)
                {
                    returnStatement = CreateStatement(returnStatement, expressions);
                    return returnStatement;
                }

                if (keywords.TryGetValue(item, out var value))
                {
                    switch (value)
                    {
                        case 0:
                            string id = GetNextItemWithoutSpace(programText, ref i);
                            expressions.Push(new ScanExpression(new IdentifierExpression(id)));
                            break;
                        case 1:
                            string nextItem = GetNextItemWithoutSpace(programText, ref i);

                            if (nextItem == "\"")
                            {
                                var outputStr = GetString(programText, ref i);
                                outputStr = outputStr.Replace("\\n", "\n");
                                expressions.Push(new PrintExpression(new StringExpression(outputStr)));
                            }
                            else
                            {
                                var expression = nextItem + GetExpressionString(programText, ';', ref i);
                                expressions.Push(new PrintExpression(ParseExpression(expression)));
                            }
                            break;
                        case 2:
                            id = GetNextItemWithoutSpace(programText, ref i);
                            GetNextItemWithoutSpace(programText, ref i);
                            string fromEx = GetExpressionString(programText, 't', ref i);
                            GetNextItemWithoutSpace(programText, ref i);
                            string toEx = GetExpressionString(programText, '{', ref i);
                            lastStatement = ParseStatement(programText, ref i);
                            expressions.Push(new StatementExpression(lastStatement, new ForExpression(new IdentifierExpression(id),
                                ParseExpression(fromEx), ParseExpression(toEx))));
                            break;
                        case 3:
                            string firstEx = GetExpressionString(programText, new char[] { '<', '>', '=', '!' }, ref i);
                            string operation = GetNextItemWithoutSpace(programText, ref i);
                            string secondEx = GetExpressionString(programText, '{', ref i);
                            lastStatement = ParseStatement(programText, ref i);

                            ElseExpression? elseExpression = null;
                            string elseItem = GetNextItemWithoutSpace(programText, ref i);
                            {
                                if (keywords.TryGetValue(elseItem, out var res) && res == 4)
                                {
                                    StatementExpression statement = ParseStatement(programText, ref i);
                                    elseExpression = new ElseExpression(statement);
                                }
                            }

                            if (elseExpression == null)
                            {
                                expressions.Push(new StatementExpression(lastStatement, new IfExpression(new BoolExpression(ParseExpression(firstEx),
                                    ParseExpression(secondEx), operation))));
                            }
                            else
                            {
                                expressions.Push(new StatementExpression(lastStatement, new IfExpression(new BoolExpression(ParseExpression(firstEx),
                                    ParseExpression(secondEx), operation)), elseExpression));
                            }
                            break;
                    }
                }
                else
                {
                    _ = GetNextItemWithoutSpace(programText, ref i);
                    string ex = GetExpressionString(programText, ';', ref i);

                    expressions.Push(new AssignExpression(new IdentifierExpression(item), ParseExpression(ex)));
                }
            }

            returnStatement = CreateStatement(returnStatement, expressions);
            return returnStatement;
        }

        private static StatementExpression? CreateStatement(StatementExpression? returnStatement, Stack<AbstractExpression> expressions)
        {
            while (expressions.TryPop(out var ex))
            {
                if (ex is ScanExpression)
                {
                    returnStatement = new StatementExpression(statement: returnStatement, scan: (ScanExpression)ex);
                }
                if (ex is PrintExpression)
                {
                    returnStatement = new StatementExpression(statement: returnStatement, print: (PrintExpression)ex);
                }
                if (ex is AssignExpression)
                {
                    returnStatement = new StatementExpression(statement: returnStatement, assign: (AssignExpression)ex);
                }
                if (ex is StatementExpression)
                {
                    returnStatement = (StatementExpression?)ex;
                }
            }

            return returnStatement;
        }

        private ExpressionExpression ParseExpression(string expression)
        {
            ExpressionExpression? newExpression = null;
            TermExpression? term;
            var splitEx = expression.Split(new char[] { '+', '-' }, StringSplitOptions.TrimEntries);
            if (!splitEx[0].IsEqualsBracketCount())
            {
                while (!splitEx[0].IsEqualsBracketCount())
                {
                    splitEx[0] += expression[splitEx[0].Length] + splitEx[1];
                    for (int i = 1; i < splitEx.Length - 1; i++)
                    {
                        splitEx[i] = splitEx[i + 1];
                    }
                    splitEx[^1] = "";
                }
            }
            term = ParseTerm(splitEx[0]);

            if (splitEx.Length > 1 && splitEx[1] != "")
            {
                int startIndex = splitEx[0].Length + 1;
                newExpression = ParseExpression(expression[startIndex..]);
            }

            if (newExpression != null)
            {
                int startIndex = splitEx[0].Length;
                string op = GetNextItemWithoutSpace(expression, ref startIndex);
                return new ExpressionExpression(term, newExpression, op[0]);
            }

            return new ExpressionExpression(term);
        }

        private TermExpression ParseTerm(string term)
        {
            TermExpression? newTerm = null;
            FactorExpression? factor;
            var splitTerm = term.Split(new char[] { '*', '/' }, StringSplitOptions.TrimEntries);
            if (!splitTerm[0].IsEqualsBracketCount())
            {
                while (!splitTerm[0].IsEqualsBracketCount())
                {
                    splitTerm[0] += term[splitTerm[0].Length] + splitTerm[1];
                    for (int i = 1; i < splitTerm.Length - 1; i++)
                    {
                        splitTerm[i] = splitTerm[i + 1];
                    }
                    splitTerm[^1] = "";
                }
            }
            factor = ParseFactor(splitTerm[0]);

            if (splitTerm.Length > 1 && splitTerm[1] != "")
            {
                int startIndex = term.IndexOf(splitTerm[1]);
                newTerm = ParseTerm(term[startIndex..]);
            }

            if (newTerm != null)
            {
                int startIndex = splitTerm[0].Length;
                string op = GetNextItemWithoutSpace(term, ref startIndex);
                return new TermExpression(factor, newTerm, op[0]);
            }

            return new TermExpression(factor);
        }

        private FactorExpression ParseFactor(string factor)
        {
            if (int.TryParse(factor, out int result))
            {
                return new FactorExpression(new NumberExpression(result));
            }
            else if (factor[0] != '(')
            {
                return new FactorExpression(new IdentifierExpression(factor));
            }
            else
            {
                var ex = ParseExpression(factor.Trim(new char[] { '(', ')' }));
                return new FactorExpression(ex);
            }
        }

        private string GetExpressionString(string programText, char lastSymbol, ref int i)
        {
            string res = "";
            while (programText[i] != lastSymbol)
            {
                res += programText[i];
                i++;
            }
            return res.Trim();
        }

        private string GetExpressionString(string programText, char[] lastSymbol, ref int i)
        {
            string res = "";
            while (!lastSymbol.Contains(programText[i]))
            {
                res += programText[i];
                i++;
            }
            return res.Trim();
        }

        private string GetString(string programText, ref int i)
        {
            int startIndex = i;
            while (programText[i] != '\"')
            {
                i++;
            }
            i++;
            return programText[startIndex..(i - 1)];
        }

        private string GetNextItemWithoutSpace(string programText, ref int i)
        {
            var item = GetNextItem(programText, i);
            i += item.Length;

            if (string.IsNullOrEmpty(item))
            {
                return item;
            }

            while (item.IsSpace())
            {
                item = GetNextItem(programText, i);
                i += item.Length;
            }

            if (item.Length == 1 && char.IsDigit(item[0]))
            {
                while (char.IsDigit(programText[i]))
                {
                    item += programText[i];
                    i++;
                }
            }

            if (item.Length == 1 && (char.IsLetter(item[0]) || item[0] == '_'))
            {
                while (char.IsLetter(programText[i]) || item[0] == '_')
                {
                    item += programText[i];
                    i++;
                }
            }

            item = item.Trim();
            return item;
        }

        private Dictionary<string, int> GetKeywords()
        {
            Dictionary<string, int> keywords = new Dictionary<string, int>();
            keywords.Add("scan", 0);
            keywords.Add("print", 1);
            keywords.Add("for", 2);
            keywords.Add("if", 3);
            keywords.Add("else", 4);
            keywords.Add("+", 5);
            keywords.Add("-", 6);
            keywords.Add("*", 7);
            keywords.Add("/", 8);
            keywords.Add("<", 9);
            keywords.Add(">", 10);
            keywords.Add("==", 11);
            keywords.Add("!=", 12);
            keywords.Add("=", 13);
            keywords.Add("(", 14);
            keywords.Add(")", 15);
            keywords.Add("{", 16);
            keywords.Add("}", 17);
            keywords.Add(";", 18);
            keywords.Add("to", 19);
            return keywords;
        }

        private string GetNextItem(string inputStr, int i)
        {
            var startIndex = i;
            int j = 1;
            string item = "";
            while (startIndex + j <= inputStr.Length)
            {
                item = inputStr[startIndex..(startIndex + j)];
                //var items = Z.Where(x => x.StartsWith(item));
                var items = Z.Where(x => x == item);

                if (items.Count() == 1)
                {
                    item = items.First();
                    break;
                }
                if (!items.Any() || item == "$")
                {
                    item = inputStr[startIndex..(startIndex + j)];
                    j--;
                    break;
                }

                j++;
            }
            return item;
        }

        private void CreateNormalPredictSets()
        {
            var columns = new Dictionary<string, List<string>>();
            foreach (var item in Z.Except(Left))
            {
                columns.Add(item, null);
            }
            foreach (string item in Left)
            {
                List<int> indexes = GetIndexes(item);
                var predicts = PredictSet.Where(x => indexes.Contains(x.Key));
                var newColumns = new Dictionary<string, List<string>>(columns);
                foreach (var predict in predicts)
                {
                    foreach (var terminal in predict.Value)
                    {
                        newColumns[terminal] = GetRuleByIndex(predict.Key).Action;
                    }
                }
                NormalPredictSet.Add(item, newColumns);
            }

            var emptySymbolAction = new List<string>();
            emptySymbolAction.Add("~");
            foreach (var item in FirstSet)
            {
                if (item.Value.Contains("~"))
                {
                    var keys = NormalPredictSet[item.Key].Keys.ToArray();
                    foreach (var item2 in keys)
                    {
                        if (NormalPredictSet[item.Key][item2] == null)
                        {
                            NormalPredictSet[item.Key][item2] = emptySymbolAction;
                        }
                    }
                }
            }
        }

        private TransitionFunction GetRuleByIndex(int index)
        {
            int i = 0;
            foreach (var item in _rules)
            {
                if (i == index)
                {
                    return item;
                }
                i++;
            }
            return null;
        }

        private List<int> GetIndexes(string item)
        {
            int i = 0;
            List<int> result = new List<int>();
            foreach (var rule in _rules)
            {
                if (rule.SymbolFromH == item)
                {
                    result.Add(i);
                }
                i++;
            }
            return result;
        }

        private Dictionary<string, HashSet<string>> CreateFirstSets()
        {
            bool isSetChanged;
            HashSet<string> lastSymbol = new HashSet<string> { "~" };

            do
            {
                isSetChanged = false;

                foreach (var item in _rules)
                {
                    var set = FirstSet[item.SymbolFromH];
                    set = Union(set, CollectSet(set, item.Action, lastSymbol));
                    if (FirstSet[item.SymbolFromH].Count != set.Count)
                    {
                        FirstSet[item.SymbolFromH] = new HashSet<string>(set);
                        isSetChanged = true;
                    }
                }
            } while (isSetChanged);

            return FirstSet;
        }

        private Dictionary<string, HashSet<string>> CreateFollowSets()
        {
            string END_MARKER = "$";
            FollowSet[Left.First()].Add(END_MARKER);
            foreach (var rule in _rules)
            {
                rule.Action.Reverse();
            }

            bool isSetChanged;

            do
            {
                isSetChanged = false;
                foreach (var func in _rules)
                {
                    for (int i = 0; i < func.Action.Count; i++)
                    {
                        var item = func.Action[i];

                        if (!IsNonterminal(item)) continue;

                        var set = FollowSet[item];

                        set = Union(set, i + 1 < func.Action.Count
                            ? CollectSet(set, func.Action.GetRange(i + 1, func.Action.Count - i - 1), FollowSet[func.SymbolFromH])
                            : FollowSet[func.SymbolFromH]);

                        if (FollowSet[item].Count != set.Count)
                        {
                            FollowSet[item] = set;
                            isSetChanged = true;
                        }
                    }
                }
            } while (isSetChanged);

            foreach (var rule in _rules)
            {
                rule.Action.Reverse();
            }
            return FollowSet;
        }

        private Dictionary<int, HashSet<string>> CreatePredictSets()
        {
            var EMPTY_CHAIN = "~";
            int i = 0;
            foreach (var rule in _rules)
            {
                rule.Action.Reverse();
            }

            foreach (var func in _rules)
            {
                var firstItem = func.Action[0];
                var set = new HashSet<string>();

                if (IsNonterminal(firstItem))
                {
                    set = Union(set, CollectSet(set, func.Action.GetRange(0, 1), FollowSet[func.SymbolFromH]));
                }
                else if (firstItem == EMPTY_CHAIN)
                {
                    set = new HashSet<string>(FollowSet[func.SymbolFromH]);
                }
                else
                {
                    set.Add(firstItem.ToString());
                }

                PredictSet[i] = set;
                i++;
            }

            foreach (var rule in _rules)
            {
                rule.Action.Reverse();
            }
            return PredictSet;
        }

        private HashSet<string> CollectSet(HashSet<string> initialSet, List<string> items, HashSet<string> additionalSet)
        {
            var EMPTY_CHAIN = "~";

            var set = initialSet;

            for (int i = 0; i < items.Count; i++)
            {
                string item = items[i];
                if (IsNonterminal(item))
                {
                    set = Union(initialSet, FirstSet[item].Where(s => s != EMPTY_CHAIN).ToHashSet());

                    if (FirstSet[item].Contains(EMPTY_CHAIN))
                    {
                        if (i + 1 < items.Count) continue;
                        set = Union(set, additionalSet);
                    }
                }
                else
                {
                    HashSet<string> newSet = new HashSet<string>
                    {
                        item.ToString()
                    };
                    set = Union(initialSet, newSet);
                }
            }

            return set;
        }

        private bool IsNonterminal(string item)
        {
            return FirstSet.ContainsKey(item);
        }

        private void InitFirstFollowSets()
        {
            foreach (var item in Sigma)
            {
                if (Left.Contains(item.SymbolFromH) && !FirstSet.ContainsKey(item.SymbolFromH))
                {
                    FirstSet.Add(item.SymbolFromH, new HashSet<string>());
                    FollowSet.Add(item.SymbolFromH, new HashSet<string>());
                }
            }

            _rules = Sigma.Where(s => FirstSet.ContainsKey(s.SymbolFromH)).ToHashSet();
        }

        private static HashSet<string> Union(HashSet<string> arg1, HashSet<string> arg2)
        {
            HashSet<string> result = new HashSet<string>();
            foreach (var item in arg1)
            {
                result.Add(item);
            }
            foreach (var item in arg2)
            {
                result.Add(item);
            }
            return result;
        }
    }
}
