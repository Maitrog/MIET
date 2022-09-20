using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Threading;

namespace lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            Thread.CurrentThread.CurrentCulture = CultureInfo.InvariantCulture;
            string input = Console.ReadLine();
            Calculator calculator = new Calculator(input);

            Console.WriteLine(calculator.Calculate());
            Console.WriteLine(calculator.GetRPN());
        }
    }
}