using System;
using System.Collections.Generic;
using System.IO;

namespace lab3
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string path = @"C:\Users\Mihay\Documents\MIET\7 semester\ТАЯК\ТАЯК\Laba3\test1.txt";

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

            while (true)
            {
                string inputStr = Console.ReadLine();
                bool isSolve = pushdownAutomaton.TrySolve(inputStr);
                Console.WriteLine("Возможность разобрать строку: " + isSolve);
                Console.WriteLine(pushdownAutomaton.TrySolveDeep(inputStr));
            }

        }
    }
}
