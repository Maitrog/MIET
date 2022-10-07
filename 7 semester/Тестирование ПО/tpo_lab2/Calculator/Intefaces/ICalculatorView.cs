using System;
using System.Collections.Generic;
using System.Text;

namespace Calculator.Intefaces
{
    public interface ICalculatorView
    {
        /**
         * Displays the result of the calculation
         */
        void PrintResult(double result);

        /**
         * Shows an error, such as division by 0, empty arguments, etc.
         */
        void DisplayError(string message);

        /**
         * Returns the value entered in the first argument field
         */
        string GetFirstArgumentAsString();

        /**
         * Returns the value entered in the second argument field
         */
        string GetSecondArgumentAsString();
    }
}
