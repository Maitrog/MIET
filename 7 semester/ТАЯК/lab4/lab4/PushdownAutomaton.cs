using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace lab4
{
    internal class PushdownAutomaton
    {
        readonly HashSet<State> S;
        readonly HashSet<string> P;
        readonly HashSet<string> Z;
        readonly State s0;
        readonly string h0;
        readonly HashSet<State> F;
        readonly Dictionary<string, HashSet<string>> FirstSet;
        readonly Dictionary<string, HashSet<string>> FollowSet;
        readonly Dictionary<int, HashSet<string>> PredictSet;
        readonly HashSet<string> Left;
        HashSet<TransitionFunction> _rules;
        readonly Dictionary<string, Dictionary<string, List<string>>> NormalPredictSet;

        public HashSet<TransitionFunction> Sigma { get; }

        public PushdownAutomaton()
        {
            S = new HashSet<State>();
            P = new HashSet<string>();
            Z = new HashSet<string>();
            s0 = new State("s0");
            h0 = "$";
            F = new HashSet<State>() { s0 };
            FirstSet = new Dictionary<string, HashSet<string>>();
            FollowSet = new Dictionary<string, HashSet<string>>();
            PredictSet = new Dictionary<int, HashSet<string>>();
            Sigma = new HashSet<TransitionFunction>();
            Left = new HashSet<string>();
            NormalPredictSet = new Dictionary<string, Dictionary<string, List<string>>>();
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
                    if (item2 != "`")
                    {
                        Left.Add(transitionFunction.SymbolFromH);
                    }
                }

                P.Add(transitionFunction.SymbolFromH);
            }
        }

        #region TrySolveDeep
        //public bool TrySolveDeep(string inputStr)
        //{
        //    State currentState = s0;
        //    Stack<char> memory = new Stack<char>();
        //    memory.Push(h0);
        //    memory.Push('E');
        //    Stack<(int, int, int, State, Stack<char>)> choose = new Stack<(int, int, int, State, Stack<char>)>();

        //    for (int i = 0; i < inputStr.Length; i++)
        //    {
        //        int numberOfSkipedElement = 0;
        //        var item = inputStr[i];

        //        var functions = Sigma.Where(tr => (tr.Symbol == item || tr.Symbol == '`') && tr.CurrentState == currentState && tr.SymbolFromH == memory.Peek());

        //        if (functions.Count() == 0)
        //        {
        //            if (choose.TryPeek(out var lastChoose))
        //            {
        //                if (lastChoose.Item2 == lastChoose.Item3 - 1)
        //                {
        //                    choose.Pop();
        //                    if (i == inputStr.Length - 1 && memory.Peek() != '$')
        //                    {
        //                        i--;
        //                    }
        //                    continue;
        //                }
        //                else
        //                {
        //                    i = lastChoose.Item1;
        //                    currentState = lastChoose.Item4;
        //                    memory = new Stack<char>(lastChoose.Item5.Reverse());
        //                    lastChoose.Item2++;
        //                    numberOfSkipedElement = lastChoose.Item2;

        //                    choose.Pop();
        //                    choose.Push(lastChoose);
        //                }
        //            }
        //        }
        //        else if (functions.Count() > 1)
        //        {
        //            var newMemory = new Stack<char>(memory.Reverse());
        //            choose.Push((i, 0, functions.Count(), currentState, newMemory));
        //        }

        //        var f = functions.Skip(numberOfSkipedElement).First();
        //        currentState = f.NextState;
        //        memory.Pop();
        //        if (f.Action.Length != 1 || f.Action[0] != '`')
        //        {
        //            for (int i1 = f.Action.Length - 1; i1 >= 0; i1--)
        //            {
        //                char item2 = f.Action[i1];
        //                memory.Push(item2);
        //            }
        //        }

        //        if (f.Symbol == '`' || (i == inputStr.Length - 1 && memory.Peek() != '$'))
        //        {
        //            i--;
        //        }
        //    }

        //    if (!F.Contains(currentState) || memory.Peek() != '$')
        //    {
        //        return false;
        //    }
        //    return true;
        //}
        #endregion

        #region TrySolve
        //public bool TrySolve(string inputStr)
        //{
        //    int count = 0;
        //    State currentState = s0;
        //    Stack<char> memory = new Stack<char>();
        //    memory.Push(h0);
        //    Queue<(int, TransitionFunction, State, Stack<char>)> chooses = new Queue<(int, TransitionFunction, State, Stack<char>)>();

        //    var newMemory = new Stack<char>(memory.Reverse());
        //    var firstFunc = new TransitionFunction(new State("s0"), new State("s0"), '`', '$', "E$");
        //    chooses.Enqueue((0, firstFunc, currentState, newMemory));


        //    for (int i = 0; i < inputStr.Length; i++)
        //    {
        //        var item = inputStr[i];

        //        if (!chooses.TryDequeue(out var currentChoose) || count == 100000)
        //        {
        //            break;
        //        }
        //        i = currentChoose.Item1;
        //        currentState = currentChoose.Item3;
        //        memory = new Stack<char>(currentChoose.Item4.Reverse());
        //        var f = currentChoose.Item2;

        //        currentState = f.NextState;
        //        memory.Pop();
        //        if (f.Action.Length != 1 || f.Action[0] != '`')
        //        {
        //            for (int i1 = f.Action.Length - 1; i1 >= 0; i1--)
        //            {
        //                char item2 = f.Action[i1];
        //                memory.Push(item2);
        //            }
        //        }

        //        if (f.Symbol == '`' || (i == inputStr.Length - 1 && memory.Peek() != '$'))
        //        {
        //            i--;
        //        }

        //        if (memory.Count != 0)
        //        {
        //            if (i + 1 < inputStr.Length)
        //            {
        //                item = inputStr[i + 1];
        //            }
        //            else
        //            {
        //                continue;
        //            }
        //            var functions = Sigma.Where(tr => (tr.Symbol == item || tr.Symbol == '`') && tr.CurrentState == currentState && tr.SymbolFromH == memory.Peek());

        //            for (int j = 0; j < functions.Count(); j++)
        //            {
        //                newMemory = new Stack<char>(memory.Reverse());
        //                var func = functions.Skip(j).First();
        //                chooses.Enqueue((i + 1, func, currentState, newMemory));
        //            }
        //            if (i == inputStr.Length - 1 && memory.Peek() == '$')
        //            {
        //                break;
        //            }
        //        }
        //        count++;
        //    }

        //    if (!F.Contains(currentState) || memory.Count == 0 || memory.Peek() != '$')
        //    {
        //        return false;
        //    }
        //    return true;
        //}
        #endregion

        public void FindError(string inputStr)
        {
            InitFirstFollowSets();
            CreateFirstSets();
            CreateFollowSets();
            CreatePredictSets();
            if (NormalPredictSet.Count == 0)
            {
                CreateNormalPredictSets();
            }

            int errorCount = 0;
            Stack<string> memory = new Stack<string>();
            memory.Push("$");
            memory.Push("program");

            for (int i = 0; i < inputStr.Length; i++)
            {
                string item = GetNextItem(inputStr, i);

                if (memory.TryPeek(out string c) && c != "$")
                {
                    bool isNonterminal = IsNonterminal(c);
                    if (!isNonterminal && c != item || isNonterminal && (!NormalPredictSet[c].ContainsKey(item) || NormalPredictSet[c][item] == null))
                    {
                        do
                        {
                            Console.WriteLine($"Error! Index: {i}. Symbol: {item}.");
                            errorCount++;
                            i += item.Length;
                            item = GetNextItem(inputStr, i);
                        } while (isNonterminal && (!FirstSet[c].Contains(item) || FollowSet[c].Contains(item)));
                    }
                    memory.Pop();
                    if (c == item)
                    {
                        i += item.Length - 1;
                    }
                    else
                    {
                        i--;
                        if (!string.IsNullOrEmpty(item))
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

            Console.WriteLine($"Number of errors: {errorCount}.");
        }

        private string GetNextItem(string inputStr, int i)
        {
            var startIndex = i;
            int j = 1;
            string item = "";
            while (startIndex + j <= inputStr.Length)
            {
                item = inputStr[startIndex..(startIndex + j)];
                var items = Z.Where(x => x.StartsWith(item));
                if (items.Count() == 1)
                {
                    item = items.First();
                    break;
                }
                if (items.Count() == 0 || item == "$")
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
