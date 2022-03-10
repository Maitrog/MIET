namespace lab2_csharp
{
    public class Program
    {
        public static void Main(string[] args)
        {
            double a, b, c, d, e, f;
            a = double.Parse(Console.ReadLine());
            b = double.Parse(Console.ReadLine());
            c = double.Parse(Console.ReadLine());
            d = double.Parse(Console.ReadLine());
            e = double.Parse(Console.ReadLine());
            f = double.Parse(Console.ReadLine());
            if (a == 0 && b == 0 && c == 0 && d == 0 && e == 0 && f == 0)
            {
                Console.Write("5");
            }
            else if (a * d - c * b != 0 && (e * d - b * f != 0 || a * f - c * e != 0))
            {
                double y = (a * f - c * e) / (a * d - c * b);
                double x = (d * e - b * f) / (d * a - b * c);
                Console.Write($"2 {x} {y}");
            }
            else if (a * d - c * b == 0 && (e * d - b * f != 0 || a * f - c * e != 0) ||
                a == 0 && c == 0 && e / b != f / d ||
                b == 0 && d == 0 && e / a != f / c ||
                a == 0 && b == 0 && c == 0 && d == 0 && e / f > 0)
            {
                if (a == 0 && b == 0 && e == 0 && d != 0 && c == 0 ||
                    c == 0 && d == 0 && f == 0 && b != 0 && a == 0)
                {
                    double y = -8888;
                    if (b == 0)
                        y = f / d;
                    else if (d == 0)
                        y = e / b;
                    else if (e == 0 || f == 0)
                        y = 0;

                    Console.Write($"4 {y}");
                }
                else if (a == 0 && b == 0 && e == 0 && c != 0 && d == 0 ||
                    c == 0 && d == 0 && f == 0 && a != 0 && b == 0)
                {
                    double x = -8888;
                    if (a == 0)
                        x = f / c;
                    else if (c == 0)
                        x = e / a;
                    else if (e == 0 || f == 0)
                        x = 0;
                    Console.Write($"3 {x}");
                }
                else
                    Console.Write("0");
            }
            else if (a == 0 && c == 0)
            {
                double y;
                if (e == 0)
                    y = f / d;
                else if (f == 0)
                    y = e / b;
                else
                    y = e / b;
                Console.Write($"4 {y}");
            }
            else if (b == 0 && d == 0)
            {
                double x;
                if (e == 0)
                    x = f / c;
                else if (f == 0)
                    x = e / a;
                else
                    x = e / a;
                Console.Write($"3 {x}");
            }
            else if (b == 0 && e == 0)
            {
                double k, n;
                k = -c / d;
                n = f / d;
                Console.Write($"1 {k} {n}");
            }
            else if (d == 0 && f == 0)
            {
                double k, n;
                k = -a / b;
                n = e / b;
                Console.Write($"1 {k} {n}");
            }
            else if (a == 0 && e == 0)
            {
                double k, n;
                k = -d / c;
                n = f / c;
                Console.Write($"1 {k} {n}");
            }
            else if (c == 0 && f == 0)
            {
                double k, n;
                k = -b / a;
                n = e / a;
                Console.Write($"1 {k} {n}");
            }
            else if (a / b == c / d)
            {
                double k, n;
                k = -c / d;
                n = f / d;
                Console.Write($"1 {k} {n}");
            }
            else
            {
                Console.Write("Are you kidding me?");
            }

        }
    }
}