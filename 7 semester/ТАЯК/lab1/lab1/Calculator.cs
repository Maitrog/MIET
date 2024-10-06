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
                TryParse(_term, out _rpn);
                var result = CalculateRPN(_rpn);
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

            var result = string.Join(" ", _rpn);
            return result;
        }

        static double CalculateRPN(List<string> term)
        {
            string[] OPERATORS = { "+", "-", "*", "/", "log", "pow", "!"};
            var operands = new Stack<double>();

            foreach (var item in term)
            {
                if (OPERATORS.Contains(item))
                {
                    var o1 = operands.Pop();
                    operands.TryPop(out var o2);

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
            string[] operators = { "+", "-", "*", "/", "log", "pow", "!", "," };
            var parsedStr = SplitTerm(str);
            outputStr = new List<string>();
            string op;

            var operatorsStack = new Stack<string>();

            foreach (var t in parsedStr)
            {
                op = t;
                if (op == "(")
                {
                    operatorsStack.Push(op);
                }
                else if (operators.Contains(op))
                {
                    while (operatorsStack.TryPop(out var newOp))
                    {
                        if (GetRank(op) <= GetRank(newOp) && (op != "!" || newOp != "!") && (op != "log" || newOp != "!") && (op != "pow" || newOp != "!"))
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

            outputStr.RemoveAll(x => x == ",");
            return true;
        }

        static void Validate(string str)
        {
            var changeStr = Regex.Replace(str, @"\(\-+\d\)|^\-+\d", "");
            if (string.IsNullOrEmpty(str))
            {
                throw new Exception("Выражение не может быть пустым");
            }

            if (str.Contains(")("))
            {
                throw new Exception("Между скобками отсутствует знак умножения");
            }

            if (Regex.IsMatch(changeStr, "\\(([/*+]|pow(?!\\(\\d(.\\d)*,?\\d(.\\d)*\\))|log(?!\\(\\d(.\\d)*,?\\d(.\\d)*\\)))+.*\\)|\\(.*([/*+-]|pow|log)+\\)"))
            {
                throw new Exception("Выражение в скобках некорректно");
            }

            if (Regex.IsMatch(str, "\\d\\(|\\)\\d|(\\)(log|pow))"))
            {
                throw new Exception("Между числом и скобкой отсутствует знак умножения");
            }

            if (Regex.IsMatch(changeStr, "([/*+]){2,}|([/*+]|pow|log){0,}-([/*+]){1,}"))
            {
                throw new Exception("Несколько действий не могут идти подряд");
            }

            if (changeStr.Contains("pow") && !Regex.IsMatch(changeStr, @"pow\(\d*(\.\d+)?,\d*(\.\d+)?\)"))
            {
                throw new Exception("Функция pow должна иметь 2 вещественных аргумента");
            }

            if (changeStr.Contains("log") && !Regex.IsMatch(changeStr, @"log\(\d*(\.\d+)?,\d*(\.\d+)?\)"))
            {
                throw new Exception("Функция log должна иметь 2 вещественных аргумента");
            }

            if (Regex.IsMatch(str, "pow(?!\\()"))
            {
                throw new Exception("Функция pow имеет вид pow(a,b), где a и b - вещественные числа");
            }

            if (Regex.IsMatch(str, "log(?!\\()"))
            {
                throw new Exception("Функция pow имеет вид log(a,b), где a и b - вещественные положительные числа");
            }

            var s = new Stack<char>();
            foreach (var item in str)
            {
                switch (item)
                {
                    case '(':
                        s.Push(item);
                        break;
                    case ')' when !s.TryPop(out _):
                        throw new Exception("Неверный порядок скобок");
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
            string[] OPERATORS_2 = { "+", "-", "*", "/", "," };
            string[] OPERATORS_3 = { "log", "pow" };
            string op;

            var operands = str.Split(OPERATORS, StringSplitOptions.RemoveEmptyEntries);
            var result = new List<string>();

            var skiped = 0;
            var elem = 0;
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
                "," => 2,
                "+" => 3,
                "-" => 3,
                "*" => 4,
                "/" => 4,
                "log" => 5,
                "pow" => 5,
                "!" => 6,
                _ => -1,
            };
        }

        static string ClearSpace(string str)
        {
            return str.Replace(" ", "");
        }
    }
}
