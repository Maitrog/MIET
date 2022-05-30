using System.Diagnostics;
using System.Text.RegularExpressions;

Random Random = new Random();
string[] phones = new string[100000];
for (long i = 0; i < phones.Length; i++)
{
    phones[i] = Random.NextInt64(10000000000, 99999999999).ToString();
    phones[i] = phones[i].Insert(0, "+");
    phones[i] = phones[i].Insert(2, " (");
    phones[i] = phones[i].Insert(7, ") ");
    phones[i] = phones[i].Insert(12, "-");
    phones[i] = phones[i].Insert(15, "-");
}

var stopwatch = Stopwatch.StartNew();
stopwatch.Start();
foreach (var item in phones)
{
    if (!RegexValidation(item))
    {
        Console.WriteLine("Regex: " + item);
    }
}
stopwatch.Stop();
Console.WriteLine(stopwatch.Elapsed.TotalMilliseconds);

stopwatch.Restart();
foreach (var item in phones)
{
    if (!ReplaceSimbolValidation(item))
    {
        Console.WriteLine("ReplaceSimbol: " + item);
    }
}
stopwatch.Stop();
Console.WriteLine(stopwatch.Elapsed.TotalMilliseconds);

stopwatch.Restart();
foreach (var item in phones)
{
    if (!ReplaceSimbolAndRegexValidation(item))
    {
        Console.WriteLine("ReplaceSimbolAndRegex: " + item);
    }
}
stopwatch.Stop();
Console.WriteLine(stopwatch.Elapsed.TotalMilliseconds);


bool RegexValidation(string phone)
{
    return Regex.IsMatch(phone, @"^\+?\d\s?\(\d{3}\)\s?\d{3}[\s-]?\d{2}[\s-]?\d{2}|
                ^\+?\d\s?\d{3}[\s-]?\d{3}[\s-]?\d{2}[\s-]?\d{2}");
}

bool ReplaceSimbolValidation(string phone)
{
    phone = phone.Replace(" ", "")
        .Replace("(", "")
        .Replace(")", "")
        .Replace("-", "")
        .Replace("+", "");
    if (phone.Length == 11)
    {
        foreach (var item in phone)
        {
            if (item < '0' || item > '9')
            {
                return false;
            }
        }
    }
    return true;
}

bool ReplaceSimbolAndRegexValidation(string phone)
{
    phone = phone.Replace(" ", "")
        .Replace("(", "")
        .Replace(")", "")
        .Replace("-", "")
        .Replace("+", "");
    return Regex.IsMatch(phone, @"^\d{11}");
}