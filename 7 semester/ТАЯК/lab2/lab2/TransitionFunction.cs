using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace lab2
{
    internal class TransitionFunction
    {
        public State CurrentState { get; }
        public State NextState { get; }
        public char Symbol { get; }

        public TransitionFunction(State currentState, State nextState, char symbol)
        {
            CurrentState = currentState;
            NextState = nextState;
            Symbol = symbol;
        }

        public TransitionFunction(string currentState, string nextState, char symbol)
        {
            CurrentState = new State(currentState);
            NextState = new State(nextState);
            Symbol = symbol;
        }

        public static bool TryParse(string str, out TransitionFunction tr)
        {
            tr = null;
            char firstState;
            char secondState;
            string firstNumber = "";
            string secondNumber = "";
            char symbol;

            if (string.IsNullOrEmpty(str))
            {
                return false;
            }

            if (str[0] != 'q' && str[0] != 'f')
            {
                return false;
            }
            else
            {
                firstState = str[0];
            }
            
            int i = 1;
            int j = i;
            while (str[j] >= '0' && str[j] <= '9')
            {
                firstNumber += str[j];
                j++;
            }
            
            if (j == i)
            {
                return false;
            }

            i = j;
            if(str[i] != ',')
            {
                return false;
            }

            i++;

            symbol = str[i];
            i++;

            if(str[i] != '=')
            {
                return false;
            }
            i++;
            

            if(str[i] != 'q' & str[i] != 'f')
            {
                return false;
            }
            else
            {
                secondState = str[i];
            }

            i++;

            j = i;
            while (j < str.Length && str[j] >= '0' && str[j] <= '9')
            {
                secondNumber += str[j];
                j++;
            }
            
            if (j == i)
            {
                return false;
            }

            tr = new TransitionFunction(new State(firstState + firstNumber), new State(secondState + secondNumber), symbol);
            return true;
        }

        public override string ToString()
        {
            string str = CurrentState.Name + "," + Symbol + "=" + NextState.Name;
            return str;
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(CurrentState, NextState, Symbol);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TransitionFunction))
            {
                return false;
            }
            return object.Equals(CurrentState, (obj as TransitionFunction).CurrentState) && object.Equals(NextState, (obj as TransitionFunction).NextState) && Symbol == (obj as TransitionFunction).Symbol;
        }
    }
}
