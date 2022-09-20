using System;
using System.Collections.Generic;
using System.IO;

namespace lab3
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string path = @"C:\Users\Mihay\Documents\MIET\7 semester\ТАЯК\ТАЯК\Laba3\test4.txt";

            var lines = File.ReadAllLines(path);

            PushdownAutomaton pushdownAutomaton = new PushdownAutomaton();

            foreach (var item in lines)
            {
                TransitionFunction.TryParse(item, out var result);
                pushdownAutomaton.AddRangeTransitionFunction(result);
            }

            foreach (var item in pushdownAutomaton.Sigma)
            {
                Console.WriteLine(item);
            }

            Stack<char> startStack = new Stack<char>();
            startStack.Push('_');
            startStack.Push('E');

            Console.WriteLine(pushdownAutomaton.TrySolve("a+a*a", startStack));
        }
    }
}
