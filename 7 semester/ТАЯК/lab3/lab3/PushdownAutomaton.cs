using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace lab3
{
    internal class PushdownAutomaton
    {
        readonly HashSet<State> S;
        readonly HashSet<char> P;
        readonly HashSet<char> Z;
        readonly State s0;
        readonly char h0;
        readonly HashSet<State> F;
        public HashSet<TransitionFunction> Sigma { get; }


        public PushdownAutomaton()
        {
            S = new HashSet<State>();
            P = new HashSet<char>();
            Z = new HashSet<char>();
            s0 = new State("s0");
            h0 = '_';
            F = new HashSet<State>() { s0 };
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
                            if (i == inputStr.Length - 1 && memory.Peek() != '_')
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
                    //foreach (var item2 in f.Action)
                    //{
                    //    memory.Push(item2);
                    //}
                    for (int i1 = f.Action.Length - 1; i1 >= 0; i1--)
                    {
                        char item2 = f.Action[i1];
                        memory.Push(item2);
                    }
                }

                if (f.Symbol == '`' || (i == inputStr.Length - 1 && memory.Peek() != '_'))
                {
                    i--;
                }
            }

            if (!F.Contains(currentState) || memory.Peek() != '_')
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
            var firstFunc = new TransitionFunction(new State("s0"), new State("s0"), '`', '_', "E_");
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
                    //foreach (var item2 in f.Action)
                    //{
                    //    memory.Push(item2);
                    //}
                    for (int i1 = f.Action.Length-1; i1 >= 0; i1--)
                    {
                        char item2 = f.Action[i1];
                        memory.Push(item2);
                    }
                }

                if (f.Symbol == '`' || (i == inputStr.Length - 1 && memory.Peek() != '_'))
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
                    if (i == inputStr.Length - 1 && memory.Peek() == '_')
                    {
                        break;
                    }
                }
                count++;
            }

            if (!F.Contains(currentState) || memory.Count == 0 || memory.Peek() != '_')
            {
                return false;
            }
            return true;
        }
    }
}
