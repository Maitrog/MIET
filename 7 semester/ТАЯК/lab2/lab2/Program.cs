using System;
using System.IO;

namespace lab2
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //string path = @"C:\Users\Mihay\Documents\MIET\7 semester\ТАЯК\ТАЯК\Laba2\test2.txt";
            string path = Console.ReadLine();
            string inputStr = Console.ReadLine();


            FSM fsm = new FSM();

            var fileText = File.ReadAllLines(path);
            foreach (var item in fileText)
            {
                if (!fsm.TryAddTransitionFunction(item))
                {
                    Console.WriteLine("Невозможно добавить функцию перехода");
                    return;
                }
            }

            foreach (var item in fsm.t)
            {
                Console.WriteLine(item);
            }

            bool isDeterministic = fsm.IsDeterministic();
            Console.WriteLine(isDeterministic);
            if (!isDeterministic)
            {
                var dfsm = fsm.CreateDFSM();
                foreach (var item in dfsm.t)
                {
                    Console.WriteLine(item);
                }

                Console.WriteLine("Детерминированность: {0}",dfsm.IsDeterministic());
            }

            Console.WriteLine("Возможность разобрать строку {0}: {1}",inputStr,fsm.TrySolve(inputStr));
            //Console.WriteLine(fsm.TrySolve("ab"));
            //Console.WriteLine(fsm.TrySolve("ba"));
            //Console.WriteLine(fsm.TrySolve("b"));
            //Console.WriteLine(fsm.TrySolve("ak"));
            //Console.WriteLine(fsm.TrySolve("bad"));

        }
    }
}
