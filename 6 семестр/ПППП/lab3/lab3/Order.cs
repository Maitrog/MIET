using lab3.Composite;
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
            int[] path = new int[Constants.SIZE];
            for (int i = 0; i < Constants.SIZE; i++)
            {
                path[i] = -1;
            }
            path = Optim(mat, start, finish);
            int count = 0;
            for (int i = 0; i < Constants.SIZE; i++)
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
            int[,] matrix = new int[Constants.SIZE, Constants.SIZE];
            for (int i = 0; i < Constants.SIZE; i++)
            {
                for (int j = 0; j < Constants.SIZE; j++)
                {
                    matrix[i, j] = Constants._matrixDist[i, j];
                }
            }
            switch (type)
            {
                case Type.Economy:
                    for (int i = 0; i < Constants.SIZE; i++)
                    {
                        if (Constants._points[i].Contains("TS"))
                            for (int j = 0; j < Constants.SIZE; j++)
                                matrix[i, j] = 99999;
                    }
                    goto case Type.Standart;
                case Type.Standart:
                    for (int i = 0; i < Constants.SIZE; i++)
                    {
                        if (Constants._points[i].Contains("AP"))
                            for (int j = 0; j < Constants.SIZE; j++)
                                matrix[i, j] = 99999;
                    }
                    goto case Type.Turbo;
                case Type.Turbo:
                    for (int i = 0; i < Constants.SIZE; i++)
                    {
                        for (int j = 0; j < Constants.SIZE; j++)
                            if (matrix[i, j] == 0)
                                matrix[i, j] = 99999;
                    }
                    break;
            }
            return matrix;
        }
        public int[] Optim(int[,] arr, int beginPoint, int endPoint)
        {
            int[] d = new int[Constants.SIZE];
            int[] v = new int[Constants.SIZE];
            int temp, minindex, min;
            int begin_index = beginPoint;

            for (int i = 0; i < Constants.SIZE; i++)
            {
                d[i] = 99999;
                v[i] = 1;
            }
            d[begin_index] = 0;

            do
            {
                minindex = 99999;
                min = 99999;
                for (int i = 0; i < Constants.SIZE; i++)
                {
                    if ((v[i] == 1) && (d[i] < min))
                    {
                        min = d[i];
                        minindex = i;
                    }
                }

                if (minindex != 99999)
                {
                    for (int i = 0; i < Constants.SIZE; i++)
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

            int[] ver = new int[Constants.SIZE];
            int end = endPoint;
            ver[0] = end;
            int k = 1;
            int weight = d[end];

            while (end != begin_index)
            {
                for (int i = 0; i < Constants.SIZE; i++)
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
            foreach (var item in Constants._towns)
            {
                if (str == item.Key)
                    return item.Value;
            }
            return -1;
        }
    }
}
