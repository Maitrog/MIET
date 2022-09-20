using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace lab1
{
    internal class Calculator
    {
        private readonly string _term;
        private List<string> _rpn = new List<string>();
        public Calculator(string term)
        {
            _term = term;
        }
        public double Calculate()
        {
            try
            {
                GetRPN();
                TryParse(_term, out _rpn);
                double result = CalculateRPN(_rpn);
                return result;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return 0;
            }
        }

        public string GetRPN()
        {
            if (_rpn.Count == 0)
            {
                TryParse(_term, out _rpn);
            }

            string result = string.Join(" ", _rpn);
            return result;
        }

        static double CalculateRPN(List<string> term)
        {
            string[] OPERATORS = { "+", "-", "*", "/", "log", "pow", "!" };
            Stack<double> operands = new Stack<double>();

            foreach (var item in term)
            {
                if (OPERATORS.Contains(item))
                {
                    double o1 = operands.Pop();
                    operands.TryPop(out double o2);

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
                            if (o1 == 0)
                            {
                                throw new Exception("Нельзя делить на 0");
                            }
                            o1 = o2 / o1;
                            break;
                        case "log":
                            if (o2 <= 0 || o2 == 1)
                            {
                                throw new Exception("Основание логарифма должно быть больше 0 и не равно 1");
                            }
                            if (o1 <= 0)
                            {
                                throw new Exception("Подлогарифмическое выражение должно быть больше 0");
                            }
                            o1 = Math.Log(o2, o1);
                            break;
                        case "pow":
                            if (o1 <= 0 && o2 > -1 && o2 < 1)
                            {
                                throw new Exception("Отрицательные числа нельзя возводить в степень по модулю меньше 1");
                            }
                            o1 = Math.Pow(o2, o1);
                            break;
                        case "!":
                            o1 = (-o1);
                            operands.Push(o2);
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
            Validate(str);
            str = ClearSpace(str);
            string[] operators = { "+", "-", "*", "/", "log", "pow", "!" };
            var parsedStr = SplitTerm(str);
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
                        if (GetRank(op) <= GetRank(newOp) && (op != "!" || newOp != "!"))
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
                    if (operatorsStack.TryPop(out op))
                    {
                        if (op == "log" || op == "pow" || op == "!")
                        {
                            outputStr.Add(op);
                        }
                        else
                        {
                            operatorsStack.Push(op);
                        }
                    }
                }
                else
                {
                    outputStr.Add(op);
                }
            }
            while (operatorsStack.TryPop(out op))
            {
                outputStr.Add(op);
            }

            return true;
        }

        static void Validate(string str)
        {
            if (string.IsNullOrEmpty(str))
            {
                throw new Exception("Выражение не может быть пустым");
            }

            if (str.Contains(")("))
            {
                throw new Exception("Между скобками отсутствует знак умножения");
            }

            if (Regex.IsMatch(str, "\\d\\(|\\)\\d"))
            {
                throw new Exception("Между числом и скобкой отсутствует знак умножения");
            }

            Stack<char> s = new Stack<char>();
            foreach (var item in str)
            {
                if (item == '(')
                {
                    s.Push(item);
                }
                if (item == ')')
                {
                    if (!s.TryPop(out _))
                    {
                        throw new Exception("Неверный порядок скобок");
                    }
                }
            }
            if (s.Count > 0)
            {
                throw new Exception($"Отсутствуют закрывающие скобки: {s.Count}");
            }
        }

        static List<string> SplitTerm(string str)
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
                if (skiped == 0)
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
                    while (true)
                    {
                        op = string.Join("", str.Skip(skiped).Take(1));
                        if (op == "-")
                        {
                            result.Add("!");
                            skiped++;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                op = string.Join("", str.Skip(skiped).Take(operands[elem].Length));
                if (op == operands[elem])
                {
                    skiped += operands[elem].Length;
                    result.Add(operands[elem]);
                    elem++;
                }
                else
                {
                    op = string.Join("", str.Skip(skiped).Take(1));
                }
                if (op == ",")
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
                    else if (op == "-")
                    {
                        result.Add("!");
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
                        else if (op == "(")
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
                if (elem == operands.Length)
                {
                    break;
                }
            }
            return result;
        }

        static int GetRank(string op)
        {
            return op switch
            {
                "(" => 1,
                ")" => 1,
                "+" => 2,
                "-" => 2,
                "*" => 3,
                "/" => 3,
                "log" => 4,
                "pow" => 4,
                "!" => 5,
                _ => -1,
            };
        }

        static string ClearSpace(string str)
        {
            return str.Replace(" ", "");
        }
    }
}
