using System;
using System.Collections.Generic;
using System.Text;

namespace lab3
{
    internal class TransitionFunction
    {
        public State CurrentState { get; }
        public State NextState { get; }
        public char Symbol { get; }
        public char SymbolFromH { get; }
        public string Action { get; }

        public TransitionFunction(State currentState, State nextState, char symbol, char symbolFromH, string action)
        {
            CurrentState = currentState;
            NextState = nextState;
            Symbol = symbol;
            SymbolFromH = symbolFromH;
            Action = action;
        }

        public override string ToString()
        {
            string str = "(" + CurrentState.Name + ", " + Symbol + ", " + SymbolFromH + ") = (" + NextState.Name + ", " + Action + ")";
            return str;
        }

        public static bool TryParse(string inputStr, out HashSet<TransitionFunction> transitionFunction)
        {
            var startState = new State("s0");

            transitionFunction = null;
            if (string.IsNullOrEmpty(inputStr))
            {
                return false;
            }

            inputStr = inputStr.Replace(" ", "");

            int i = 0;
            if (!char.IsUpper(inputStr[i]))
            {
                return false;
            }
            char symbolFromH = inputStr[i];
            i++;

            if (inputStr[i] != '>')
            {
                return false;
            }
            i++;
            int j = i;

            transitionFunction = new HashSet<TransitionFunction>();
            while (i < inputStr.Length)
            {
                string term = "";
                while (i < inputStr.Length && inputStr[i] != '|')
                {
                    term += inputStr[i];
                    i++;
                }
                TransitionFunction func = new TransitionFunction(startState, startState, '`', symbolFromH, term);
                transitionFunction.Add(func);
                i++;
            }

            if (transitionFunction.Count == 0)
            {
                transitionFunction = null;
                return false;
            }

            while (j < inputStr.Length)
            {
                if (!char.IsUpper(inputStr[j]) && inputStr[j] != '|')
                {
                    TransitionFunction func = new TransitionFunction(startState, startState, inputStr[j], inputStr[j], "`");
                    transitionFunction.Add(func);
                }
                j++;
            }

            TransitionFunction f = new TransitionFunction(startState, startState, '`', '_', "`");
            transitionFunction.Add(f);
            return true;
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(CurrentState, NextState, Symbol, SymbolFromH, Action);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TransitionFunction))
            {
                return false;
            }
            return object.Equals(CurrentState, (obj as TransitionFunction).CurrentState) && object.Equals(NextState, (obj as TransitionFunction).NextState) &&
                Action == (obj as TransitionFunction).Action && Symbol == (obj as TransitionFunction).Symbol &&
                SymbolFromH == (obj as TransitionFunction).SymbolFromH;
        }
    }
}
