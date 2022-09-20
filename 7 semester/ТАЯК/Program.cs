using System;
using System.Collections.Generic;
using System.Linq;

namespace TAYAK1
{
    class Program
    {
        static void Main(string[] args)
        {
            List<string> output;
            TryParse("0,5+0,5", out output);
            Console.Write(CalculateRPN(output));
        }

        static double CalculateRPN(List<string> term)
        {
            string[] OPERATORS = { "+", "-", "*", "/", "log", "pow" };
            Stack<double> operands = new Stack<double>();

            foreach (var item in term)
            {
                if (OPERATORS.Contains(item))
                {
                    double o1 = operands.Pop();
                    double o2 = operands.Pop();

                    switch (item)
                    {
                        case "+":
                            o1 += o2;
                            break;
                        case "-":
                            o1 = o2 - o1;
                            break;
                        case "*":
                            o1 *= o2;
                            break;
                        case "/":
                            o1 = o2 / o1;
                            break;
                        case "log":
                            o1 = Math.Log(o1, o2);
                            break;
                        case "pow":
                            o1 = Math.Pow(o1, o2);
                            break;
                    }

                    operands.Push(o1);
                }
                else
                {
                    operands.Push(Convert.ToDouble(item));
                }
            }

            return operands.Pop();
        }

        static bool TryParse(string str, out List<string> outputStr)
        {
            str = ClearString(str);
            string[] operators = { "+", "-", "*", "/", "log", "pow" };
            var parsedStr = SplitString(str);
            outputStr = new List<string>();
            string op;

            Stack<string> operatorsStack = new Stack<string>();

            for (int i = 0; i < parsedStr.Count; i++)
            {
                op = parsedStr[i];
                if (op == "(")
                {
                    operatorsStack.Push(op);
                }
                else if (operators.Contains(op))
                {
                    string newOp;

                    while (operatorsStack.TryPop(out newOp))
                    {
                        if (GetRank(op) <= GetRank(newOp))
                        {
                            outputStr.Add(newOp);
                        }
                        else
                        {
                            operatorsStack.Push(newOp);
                            break;
                        }
                    }
                    operatorsStack.Push(op);
                }
                else if (op == ")")
                {
                    op = operatorsStack.Pop();
                    while (op != "(")
                    {
                        outputStr.Add(op);
                        op = operatorsStack.Pop();
                    }
                    op = operatorsStack.Pop();
                    if (op == "log" || op == "pow")
                    {
                        outputStr.Add(op);
                    }
                    else
                    {
                        operatorsStack.Push(op);
                    }
                }
                else
                {
                    outputStr.Add(op);
                }
            }
            if(operatorsStack.TryPop(out op))
            {
                outputStr.Add(op);
            }

            return (true);
        }

        static int GetRank(string op)
        {
            switch (op)
            {
                case "(":
                    return 1;
                case ")":
                    return 1;
                case "+":
                    return 2;
                case "-":
                    return 2;
                case "*":
                    return 3;
                case "/":
                    return 3;
                case "log":
                    return 4;
                case "pow":
                    return 4;
                default:
                    return -1;
            }
        }

        static string ClearString(string str)
        {
            return str.Replace(" ", "");
        }

        static List<string> SplitString(string str)
        {
            string[] OPERATORS = { "+", "-", "*", "/", "log", "pow", "(", ")", "," };
            string[] OPERATORS_2 = { "+", "-", "*", "/" };
            string[] OPERATORS_3 = { "log", "pow" };
            string op;

            var operands = str.Split(OPERATORS, StringSplitOptions.RemoveEmptyEntries);
            List<string> result = new List<string>();

            var skiped = 0;
            int elem = 0;
            while (true)
            {
                while (true)
                {
                    op = string.Join("", str.Skip(skiped).Take(1));
                    if (op == "(")
                    {
                        result.Add(op);
                        skiped++;
                    }
                    else
                    {
                        break;
                    }
                }

                op = string.Join("", str.Skip(skiped).Take(operands[elem].Length));
                if (op == operands[elem])
                {
                    skiped += operands[elem].Length;
                    result.Add(operands[elem]);
                    elem++;
                }
                if(op == ",")
                {
                    skiped++;
                }
                op = string.Join("", str.Skip(skiped).Take(1));
                if (OPERATORS_2.Contains(op))
                {
                    result.Add(op);
                    skiped++;
                }
                else
                {
                    op = string.Join("", str.Skip(skiped).Take(3));
                    if (OPERATORS_3.Contains(op))
                    {
                        result.Add(op);
                        skiped += 3;
                    }
                }
                while (true)
                {
                    op = string.Join("", str.Skip(skiped).Take(1));
                    if (op == "(")
                    {
                        result.Add(op);
                        skiped++;
                    }
                    else if (op == ")")
                    {
                        result.Add(op);
                        skiped++;
                        op = string.Join("", str.Skip(skiped).Take(1));
                        if (OPERATORS_2.Contains(op))
                        {
                            result.Add(op);
                            skiped++;
                        }
                        else
                        {
                            op = string.Join("", str.Skip(skiped).Take(3));
                            if (OPERATORS_3.Contains(op))
                            {
                                result.Add(op);
                                skiped += 3;
                            }
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                if(elem == operands.Length)
                {
                    break;
                }
            }
            return result;
        }
    }
}
