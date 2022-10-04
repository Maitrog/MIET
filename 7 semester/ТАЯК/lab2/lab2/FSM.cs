using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace lab2
{
    internal class FSM
    {
        HashSet<State> Q;
        HashSet<char> T;
        State q0;
        HashSet<State> F;
        public HashSet<TransitionFunction> t { get; }
        public FSM()
        {
            T = new HashSet<char>();
            Q = new HashSet<State>();
            q0 = new State("q0");
            F = new HashSet<State>();
            t = new HashSet<TransitionFunction>();
        }

        public void AddTransitionFunction(TransitionFunction function)
        {
            Q.Add(function.CurrentState);
            Q.Add(function.NextState);

            T.Add(function.Symbol);

            if (function.CurrentState.Name.Contains('f'))
            {
                F.Add(function.CurrentState);
            }
            if (function.NextState.Name.Contains('f'))
            {
                F.Add(function.NextState);
            }

            t.Add(function);
        }

        public bool TryAddTransitionFunction(string functionStr)
        {

            if (!TransitionFunction.TryParse(functionStr, out TransitionFunction function))
            {
                return false;
            }

            Q.Add(function.CurrentState);
            Q.Add(function.NextState);

            T.Add(function.Symbol);

            if (function.CurrentState.Name.Contains('f'))
            {
                F.Add(function.CurrentState);
            }
            if (function.NextState.Name.Contains('f'))
            {
                F.Add(function.NextState);
            }

            t.Add(function);

            return true;
        }

        public bool TrySolve(string inputStr)
        {
            var dfsm = CreateDFSM();
            while (!dfsm.IsDeterministic())
            {
                dfsm = dfsm.CreateDFSM();
            }
            State currentState = dfsm.q0;
            foreach (var item in inputStr)
            {
                var functions = dfsm.t.Where(tr => tr.Symbol == item && tr.CurrentState == currentState);
                if (functions.Count() != 1)
                {
                    return false;
                }

                currentState = functions.First().NextState;
            }
            if (dfsm.F.Contains(currentState))
            {
                return true;
            }
            return false;
        }

        public bool IsDeterministic()
        {
            foreach (var currentState in Q)
            {
                var functions = t.Where(tr => tr.CurrentState == currentState);
                foreach (var item in functions)
                {
                    int count = 0;
                    foreach (var item2 in functions)
                    {
                        if (item.Symbol == item2.Symbol)
                        {
                            count++;
                        }
                    }
                    if (count > 1)
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        public FSM CreateDFSM()
        {
            FSM DFSM = new FSM();
            foreach (var currentState in Q)
            {
                var functions = t.Where(tr => tr.CurrentState == currentState);
                foreach (var item in functions)
                {
                    List<State> states = new List<State>();
                    foreach (var item2 in functions)
                    {
                        if (item.Symbol == item2.Symbol)
                        {
                            states.Add(item2.NextState);
                        }
                    }
                    if (states.Count > 1)
                    {
                        states.Sort();

                        string name = "{";
                        foreach (var state in states)
                        {
                            name += state.Name + ",";
                        }
                        name = name.Remove(name.Length - 1);
                        name += "}";

                        var newState = new State(name);
                        DFSM.AddTransitionFunction(new TransitionFunction(item.CurrentState, newState, item.Symbol));
                        foreach (var state in states)
                        {
                            var funcs = t.Where(f => f.CurrentState == state);
                            foreach (var f in funcs)
                            {
                                DFSM.AddTransitionFunction(new TransitionFunction(newState, f.NextState, f.Symbol));
                            }
                        }
                    }
                    else
                    {
                        DFSM.AddTransitionFunction(item);
                    }
                }
            }
            return DFSM;
        }
    }
}
