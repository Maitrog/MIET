using System.Diagnostics;

const int N = 1000000;
int[] lp = new int[N + 1];
List<int> pr = new List<int>();
List<List<int>> result = new List<List<int>>(N);
for (int i = 0; i < N; i++)
{
    var size = (int)Math.Log10(i)+1;
    if(size < 16)
    {
        size = 16;
    }
    result.Add(new List<int>(size));
}

for (int i = 2; i <= N; ++i)
{
    if (lp[i] == 0)
    {
        lp[i] = i;
        pr.Add(i);
    }
    var count = pr.Count;
    for (int j = 0; j < count && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
    {
        lp[i * pr[j]] = pr[j];
    }
}

var prCount = pr.Count;
var a = Parallel.For(1, N, (i =>
{
    if (i == 1)
    {
        result[i - 1].Add(1);
    }
    else
    {
        var number = i;
        while (number != 1)
        {
            for (int j = 0; j < prCount; ++j)
            {
                if (number % pr[j] == 0)
                {
                    number /= pr[j];
                    result[i - 1].Add(pr[j]);
                    break;
                }
            }
        }
    }
}));

//for (int i = 0; i < result.Count-1; i++)
//{
//    string str = $"{i+1}: ";
//    List<int>? item = result[i];
//    foreach (var number in item)
//    {
//        str += $"{number}, ";
//    }
//    str = str.Trim().Trim(',');
//    Console.WriteLine(str);
//}