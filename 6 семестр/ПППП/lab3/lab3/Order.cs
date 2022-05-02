using lab3.Strategy;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    internal class Order
    {
        private const int SIZE = 16;
        private static readonly Dictionary<string, int> _towns = new()
        {
            { "Moscow", 2 },
            { "Mozhaisk", 4 },
            { "Zvenigorod", 5 },
            { "Nizhniy Novgorod", 8 },
            { "Dzerzhinsk", 10 },
            { "Volgograd", 13 },
            { "Kamishin", 15 }
        };
        private static readonly string[] _points = new string[SIZE] { "msk_AP","msk_TS","msk_WH","mzh_TS",
            "mzh_WH","zvn_WH","NN_AP","NN_TS", "NN_WH","dzr_TS","dzr_WH",
            "vlg_AP","vlg_TS","vlg_WH","kam_TS","kam_WH" };
        private static readonly int[,] _matrixDist = new int[SIZE, SIZE]
        {
            {0, 20, 30, 108, 110, 65, 398, 0, 0, 0, 0, 926, 0, 0, 0, 0},
            {20, 0, 10, 98, 100, 55, 0, 415, 0, 483, 0, 0, 937, 0, 1204, 0},
            {30, 10, 0, 108, 110, 65, 0, 0, 430, 0, 390, 0, 0, 652, 0, 1234},
            {108, 98, 108, 0, 5, 0, 0, 0, 0, 581, 0, 0, 1035, 0, 1302, 0},
            {110, 100, 110, 5, 0, 78, 0, 0, 540, 0, 500, 0, 0 ,1062, 0, 1344},
            {65, 55, 65, 0, 78, 0, 0, 0, 495, 0, 455, 0, 0, 1017, 0, 1299},
            {398, 0, 0, 0, 0, 0, 0, 19, 23, 0, 26, 828, 0, 0, 0, 0},
            {0, 415, 0, 0, 0, 0 ,19, 0, 4, 32, 0, 0, 840, 0, 919, 0},
            {0, 0, 430, 0, 540, 495, 23, 4, 0, 0, 40, 0, 0, 849, 0, 1010},
            {0, 483, 0, 581, 0, 0, 0, 32, 0, 0, 4, 0, 872, 0, 951, 0},
            {0, 0, 390, 0, 500, 455, 26, 0, 40, 4, 0, 0, 0, 889, 0, 1050},
            {926, 0, 0, 0, 0 ,0 ,828, 0, 0 ,0 ,0, 0, 15, 16, 0, 285},
            {0, 937, 0, 1035, 0, 0, 0, 840, 0, 872, 0, 15, 0, 2, 257, 281},
            {0, 0, 952, 0, 1062, 1017, 0, 0, 849, 0, 889, 16, 2, 0, 0 ,282},
            {0, 1204, 0, 1302, 0, 0, 0, 919, 0, 951, 0, 0, 257, 0, 0, 2},
            {0, 0, 1234, 0, 1344, 1299, 0, 0, 1010, 0, 1050, 285, 281, 282, 2, 0}
        };

        private double _cost;
        private int _volume;
        private string _startPoint;
        private string _finishPoint;
        private Type _type;
        private Track _track;
        private Context _context;

        public Order()
        {
            _cost = 0;
            _volume = 0;
            _startPoint = "";
            _finishPoint = "";
            _track = new();
            _type = Type.Economy;
            _context = new Context();

        }

        public Order(Type deliv, string startP, string finishP, int vol)
        {
            _startPoint = startP;
            _finishPoint = finishP;
            _type = deliv;
            _track = Best(startP, finishP, deliv, vol);
            _cost = _track.GetCost();
            _volume = vol;
            _context = new Context();
        }

        public Track Best(string startP, string finishP, Type deliv, int volume)
        {
            int start = Decr(startP);
            int finish = Decr(finishP);
            int[,] mat = MatrixUpd(deliv);
            int[] path = new int[SIZE];
            for (int i = 0; i < SIZE; i++)
            {
                path[i] = -1;
            }
            path = Optim(mat, start, finish);
            int count = 0;
            for (int i = 0; i < SIZE; i++)
            {
                if (path[i] != -1)
                {
                    count++;
                }
                else
                {
                    break;
                }
            }
            switch (count)
            {
                case 1:
                    {
                        _context.Strategy = new StrategyOneTransport();
                        break;
                    }
                case 3:
                    {
                        _context.Strategy = new StrategyThreeTransport();
                        break;
                    }
                case 5:
                    {
                        _context.Strategy = new StrategyFiveTransport();
                        break;
                    }

                case 7:
                    {
                        _context.Strategy = new StrategySevenTransport();
                        break;
                    }
            }
            return _context.ExecuteStrategy(path, volume);
        }

        public int[,] MatrixUpd(Type type)
        {
            int[,] matrix = new int[SIZE, SIZE];
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    matrix[i, j] = _matrixDist[i, j];
                }
            }
            switch (type)
            {
                case Type.Economy:
                    for (int i = 0; i < SIZE; i++)
                    {
                        if (_points[i].Contains("TS"))
                            for (int j = 0; j < SIZE; j++)
                                matrix[i, j] = 99999;
                    }
                    goto case Type.Standart;
                case Type.Standart:
                    for (int i = 0; i < SIZE; i++)
                    {
                        if (_points[i].Contains("AP"))
                            for (int j = 0; j < SIZE; j++)
                                matrix[i, j] = 99999;
                    }
                    goto case Type.Turbo;
                case Type.Turbo:
                    for (int i = 0; i < SIZE; i++)
                    {
                        for (int j = 0; j < SIZE; j++)
                            if (matrix[i, j] == 0)
                                matrix[i, j] = 99999;
                    }
                    break;
            }
            return matrix;
        }
        public int[] Optim(int[,] arr, int beginPoint, int endPoint)
        {
            int[] d = new int[SIZE];
            int[] v = new int[SIZE];
            int temp, minindex, min;
            int begin_index = beginPoint;

            for (int i = 0; i < SIZE; i++)
            {
                d[i] = 99999;
                v[i] = 1;
            }
            d[begin_index] = 0;

            do
            {
                minindex = 99999;
                min = 99999;
                for (int i = 0; i < SIZE; i++)
                {
                    if ((v[i] == 1) && (d[i] < min))
                    {
                        min = d[i];
                        minindex = i;
                    }
                }

                if (minindex != 99999)
                {
                    for (int i = 0; i < SIZE; i++)
                    {
                        if (arr[minindex, i] > 0)
                        {
                            temp = min + arr[minindex, i];
                            if (temp < d[i])
                            {
                                d[i] = temp;
                            }
                        }
                    }
                    v[minindex] = 0;
                }
            } while (minindex < 99999);

            int[] ver = new int[SIZE];
            int end = endPoint;
            ver[0] = end;
            int k = 1;
            int weight = d[end];

            while (end != begin_index)
            {
                for (int i = 0; i < SIZE; i++)
                    if (arr[end, i] != 0)
                    {
                        temp = weight - arr[end, i];
                        if (temp == d[i])
                        {
                            weight = temp;
                            end = i;
                            ver[k] = i + 1;
                            k++;
                        }
                    }
            }
            for (int i = 0; i < k / 2; i++)
                (ver[i], ver[k - 1 - i]) = (ver[k - 1 - i], ver[i]);
            //std::swap(ver[i], ver[k - 1 - i]);
            return ver;
        }
        public int Decr(string str)
        {
            foreach (var item in _towns)
            {
                if (str == item.Key)
                    return item.Value;
            }
            return -1;
        }
    }
}
