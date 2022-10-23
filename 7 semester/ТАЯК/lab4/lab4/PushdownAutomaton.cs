using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace lab4
{
    internal class PushdownAutomaton
    {
        readonly HashSet<State> S;
        readonly HashSet<char> P;
        readonly HashSet<char> Z;
        readonly State s0;
        readonly char h0;
        readonly HashSet<State> F;
        readonly Dictionary<char, HashSet<string>> FirstSet;
        readonly Dictionary<char, HashSet<string>> FollowSet;
        readonly Dictionary<int, HashSet<string>> PredictSet;
        HashSet<TransitionFunction> _rules;

        public HashSet<TransitionFunction> Sigma { get; }

        public PushdownAutomaton()
        {
            S = new HashSet<State>();
            P = new HashSet<char>();
            Z = new HashSet<char>();
            s0 = new State("s0");
            h0 = '$';
            F = new HashSet<State>() { s0 };
            FirstSet = new Dictionary<char, HashSet<string>>();
            FollowSet = new Dictionary<char, HashSet<string>>();
            PredictSet = new Dictionary<int, HashSet<string>>();
            Sigma = new HashSet<TransitionFunction>();
        }

        public void AddRangeTransitionFunction(IEnumerable<TransitionFunction> transitionFunctions)
        {
            foreach (var transitionFunction in transitionFunctions)
            {
                Sigma.Add(transitionFunction);
                S.Add(transitionFunction.CurrentState);
                S.Add(transitionFunction.NextState);

                foreach (var item2 in transitionFunction.Action)
                {
                    Z.Add(item2);
                }

                P.Add(transitionFunction.SymbolFromH);
            }
        }

        public bool TrySolveDeep(string inputStr)
        {
            State currentState = s0;
            Stack<char> memory = new Stack<char>();
            memory.Push(h0);
            memory.Push('E');
            Stack<(int, int, int, State, Stack<char>)> choose = new Stack<(int, int, int, State, Stack<char>)>();

            for (int i = 0; i < inputStr.Length; i++)
            {
                int numberOfSkipedElement = 0;
                var item = inputStr[i];

                var functions = Sigma.Where(tr => (tr.Symbol == item || tr.Symbol == '`') && tr.CurrentState == currentState && tr.SymbolFromH == memory.Peek());

                if (functions.Count() == 0)
                {
                    if (choose.TryPeek(out var lastChoose))
                    {
                        if (lastChoose.Item2 == lastChoose.Item3 - 1)
                        {
                            choose.Pop();
                            if (i == inputStr.Length - 1 && memory.Peek() != '$')
                            {
                                i--;
                            }
                            continue;
                        }
                        else
                        {
                            i = lastChoose.Item1;
                            currentState = lastChoose.Item4;
                            memory = new Stack<char>(lastChoose.Item5.Reverse());
                            lastChoose.Item2++;
                            numberOfSkipedElement = lastChoose.Item2;

                            choose.Pop();
                            choose.Push(lastChoose);
                        }
                    }
                }
                else if (functions.Count() > 1)
                {
                    var newMemory = new Stack<char>(memory.Reverse());
                    choose.Push((i, 0, functions.Count(), currentState, newMemory));
                }

                var f = functions.Skip(numberOfSkipedElement).First();
                currentState = f.NextState;
                memory.Pop();
                if (f.Action.Length != 1 || f.Action[0] != '`')
                {
                    for (int i1 = f.Action.Length - 1; i1 >= 0; i1--)
                    {
                        char item2 = f.Action[i1];
                        memory.Push(item2);
                    }
                }

                if (f.Symbol == '`' || (i == inputStr.Length - 1 && memory.Peek() != '$'))
                {
                    i--;
                }
            }

            if (!F.Contains(currentState) || memory.Peek() != '$')
            {
                return false;
            }
            return true;
        }

        public bool TrySolve(string inputStr)
        {
            int count = 0;
            State currentState = s0;
            Stack<char> memory = new Stack<char>();
            memory.Push(h0);
            Queue<(int, TransitionFunction, State, Stack<char>)> chooses = new Queue<(int, TransitionFunction, State, Stack<char>)>();

            var newMemory = new Stack<char>(memory.Reverse());
            var firstFunc = new TransitionFunction(new State("s0"), new State("s0"), '`', '$', "E$");
            chooses.Enqueue((0, firstFunc, currentState, newMemory));


            for (int i = 0; i < inputStr.Length; i++)
            {
                var item = inputStr[i];

                if (!chooses.TryDequeue(out var currentChoose) || count == 100000)
                {
                    break;
                }
                i = currentChoose.Item1;
                currentState = currentChoose.Item3;
                memory = new Stack<char>(currentChoose.Item4.Reverse());
                var f = currentChoose.Item2;

                currentState = f.NextState;
                memory.Pop();
                if (f.Action.Length != 1 || f.Action[0] != '`')
                {
                    for (int i1 = f.Action.Length - 1; i1 >= 0; i1--)
                    {
                        char item2 = f.Action[i1];
                        memory.Push(item2);
                    }
                }

                if (f.Symbol == '`' || (i == inputStr.Length - 1 && memory.Peek() != '$'))
                {
                    i--;
                }

                if (memory.Count != 0)
                {
                    if (i + 1 < inputStr.Length)
                    {
                        item = inputStr[i + 1];
                    }
                    else
                    {
                        continue;
                    }
                    var functions = Sigma.Where(tr => (tr.Symbol == item || tr.Symbol == '`') && tr.CurrentState == currentState && tr.SymbolFromH == memory.Peek());

                    for (int j = 0; j < functions.Count(); j++)
                    {
                        newMemory = new Stack<char>(memory.Reverse());
                        var func = functions.Skip(j).First();
                        chooses.Enqueue((i + 1, func, currentState, newMemory));
                    }
                    if (i == inputStr.Length - 1 && memory.Peek() == '$')
                    {
                        break;
                    }
                }
                count++;
            }

            if (!F.Contains(currentState) || memory.Count == 0 || memory.Peek() != '$')
            {
                return false;
            }
            return true;
        }

        public void FindError(string inputStr)
        {
            InitFirstFollowSets();
            CreateFirstSets();
            CreateFollowSets();
            CreatePredictSets();

            int count = 0;
            int addedFunctions = 0;
            State currentState = s0;
            Stack<char> memory = new Stack<char>();
            memory.Push(h0);
            Queue<(int, TransitionFunction, State, Stack<char>, Stack<string>)> chooses = new Queue<(int, TransitionFunction, State, Stack<char>, Stack<string>)>();

            var newMemory = new Stack<char>(memory.Reverse());
            var firstFunc = new TransitionFunction(new State("s0"), new State("s0"), '`', '$', "$E");
            Stack<string> errors = new Stack<string>();
            (int, TransitionFunction, State, Stack<char>, Stack<string>) lastChoose = (0, firstFunc, currentState, newMemory, errors);
            chooses.Enqueue((0, firstFunc, currentState, newMemory, errors));


            for (int i = 0; i < inputStr.Length; i++)
            {
                var item = inputStr[i];
                if (memory.TryPeek(out char c) && c != '$')
                {
                    bool isNonterminal = IsNonterminal(c);
                    if (!isNonterminal && c != item)
                    {
                        errors.Push($"Error. Terminal: {item}. Index: {i}");

                        i = SkipSymbol(addedFunctions, chooses, i, 1);

                        if (i + 1 >= inputStr.Length && chooses.Count > 0)
                        {
                            errors.Clear();
                            goto getNextChoose;
                        }
                        continue;
                    }
                    var rules = _rules.Where(r => r.SymbolFromH == c).ToHashSet();

                    int j = 0;
                    bool isPredict = false;
                    foreach (var rule in rules)
                    {
                        if (PredictSet[j].Contains(item.ToString()))
                        {
                            isPredict = true;
                            break;
                        }
                        j++;
                    }
                    if (isNonterminal && !isPredict)
                    {
                        errors.Push($"Error. Terminal: {item}. Index: {i}");

                        int skip = 1;

                        var first = FirstSet[c];
                        var follow = FollowSet[c];
                        while (i + skip < inputStr.Length && !first.Contains(inputStr[i + skip].ToString()) && !follow.Contains(inputStr[i + skip].ToString()))
                        {
                            skip++;
                        }

                        i = SkipSymbol(addedFunctions, chooses, i, skip);
                        if (i + 1 >= inputStr.Length && chooses.Count > 0)
                        {
                            errors.Clear();
                            goto getNextChoose;
                        }
                        continue;
                    }
                }

            getNextChoose:
                if (!chooses.TryDequeue(out var currentChoose) || count == 100000)
                {
                    break;
                }
                lastChoose = currentChoose;
                i = currentChoose.Item1;
                currentState = currentChoose.Item3;
                memory = new Stack<char>(currentChoose.Item4.Reverse());
                var f = currentChoose.Item2;
                currentState = f.NextState;
                var newErrors = new Stack<string>(currentChoose.Item5.Reverse());
                foreach (var error in errors.Reverse())
                {
                    newErrors.Push(error);
                }
                errors.Clear();

                memory.Pop();
                if (f.Action.Length != 1 || f.Action[0] != '`')
                {
                    for (int i1 = 0; i1 < f.Action.Length; i1++)
                    {
                        char item2 = f.Action[i1];
                        memory.Push(item2);
                    }
                }

                if (f.Symbol == '`' || (i == inputStr.Length - 1 && memory.Peek() != '$'))
                {
                    i--;
                }

                if (memory.Count != 0)
                {
                    if (i + 1 < inputStr.Length)
                    {
                        item = inputStr[i + 1];
                    }
                    else
                    {
                        continue;
                    }
                    var functions = Sigma.Where(tr => (tr.Symbol == item || tr.Symbol == '`') && tr.CurrentState == currentState && tr.SymbolFromH == memory.Peek());
                    addedFunctions = functions.Count();

                    for (int j = 0; j < addedFunctions; j++)
                    {
                        newMemory = new Stack<char>(memory.Reverse());
                        var func = functions.Skip(j).First();
                        chooses.Enqueue((i + 1, func, currentState, newMemory, newErrors));
                    }
                    if (i == inputStr.Length - 1 && memory.Peek() == '$')
                    {
                        break;
                    }
                }
                count++;
            }

            while (lastChoose.Item5.TryPop(out string res))
            {
                Console.WriteLine(res);
            }
        }

        private static int SkipSymbol(int addedFunctions, Queue<(int, TransitionFunction, State, Stack<char>, Stack<string>)> chooses, int i, int skip)
        {
            List<(int, TransitionFunction, State, Stack<char>, Stack<string>)> list = chooses.Reverse().ToList();
            chooses.Clear();
            for (int i1 = 0; i1 < list.Count; i1++)
            {
                (int, TransitionFunction, State, Stack<char>, Stack<string>) choose = list[i1];
                if (i1 >= list.Count - addedFunctions)
                {
                    choose.Item1 += skip;
                }
                chooses.Enqueue(choose);
            }
            i += skip - 1;
            return i;
        }

        private Dictionary<char, HashSet<string>> CreateFirstSets()
        {
            bool isSetChanged;
            HashSet<string> lastSymbol = new HashSet<string> { "$" };

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

        private Dictionary<char, HashSet<string>> CreateFollowSets()
        {
            string END_MARKER = "$";
            FollowSet[Sigma.First().SymbolFromH].Add(END_MARKER);
            foreach (var rule in _rules)
            {
                rule.Action = new string(rule.Action.Reverse().ToArray());
            }

            bool isSetChanged;

            do
            {
                isSetChanged = false;
                foreach (var func in _rules)
                {
                    for (int i = 0; i < func.Action.Length; i++)
                    {
                        var item = func.Action[i];

                        if (!IsNonterminal(item)) continue;

                        var set = FollowSet[item];

                        set = Union(set, i + 1 < func.Action.Length
                            ? CollectSet(set, func.Action[(i + 1)..], FollowSet[func.SymbolFromH])
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
                rule.Action = new string(rule.Action.Reverse().ToArray());
            }
            return FollowSet;
        }

        private Dictionary<int, HashSet<string>> CreatePredictSets()
        {
            var EMPTY_CHAIN = '$';
            int i = 0;
            foreach (var rule in _rules)
            {
                rule.Action = new string(rule.Action.Reverse().ToArray());
            }

            foreach (var func in _rules)
            {
                var firstItem = func.Action[0];
                var set = new HashSet<string>();

                if (IsNonterminal(firstItem))
                {
                    set = Union(set, CollectSet(set, func.Action[0..1], FollowSet[func.SymbolFromH]));
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
                rule.Action = new string(rule.Action.Reverse().ToArray());
            }
            return PredictSet;
        }

        private HashSet<string> CollectSet(HashSet<string> initialSet, string items, HashSet<string> additionalSet)
        {
            var set = initialSet;

            for (int i = 0; i < items.Length; i++)
            {
                char item = items[i];
                if (IsNonterminal(item))
                {
                    set = Union(initialSet, FirstSet[item].Where(s => s != "$").ToHashSet());

                    if (FirstSet[item].Contains("$"))
                    {
                        if (i + 1 < items.Length) continue;
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

        private bool IsNonterminal(char item)
        {
            return FirstSet.ContainsKey(item);
        }

        private void InitFirstFollowSets()
        {
            foreach (var item in Sigma)
            {
                if (char.IsUpper(item.SymbolFromH) && !FirstSet.ContainsKey(item.SymbolFromH))
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
