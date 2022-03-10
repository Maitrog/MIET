using System;
using System.Collections.Generic;
using System.Text;

namespace Lab6
{
    [Serializable]
    class TimeItem
    {
        public int Dimension{ get; set; }
        public int Count { get; set; }
        public double TimeUnmanagedCode { get; set; }
        public double TimeManagedCoge { get; set; }
        public double Factor { get; private set; }
        public TimeItem()
        {
            Dimension = 2;
            Count = 0;
            TimeUnmanagedCode = 0.0;
            TimeManagedCoge = 0.0;
            Factor = 1.0;
        }
        public TimeItem(int _dim, int _count, double _timeUC, double _timeMC)
        {
            Dimension = _dim;
            Count = _count;
            TimeUnmanagedCode = _timeUC;
            TimeManagedCoge = _timeMC;
            Factor = TimeManagedCoge / TimeUnmanagedCode;
        }
        public override string ToString()
        {
            return $"{Dimension}\t{Count}\t{TimeUnmanagedCode}\t{TimeManagedCoge}\t{Factor}\n";
        }

    }
}
