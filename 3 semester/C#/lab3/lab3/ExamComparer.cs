using System;
using System.Collections.Generic;
using System.Text;

namespace lab3
{
    class ExamComparer: IComparer<Exam>
    {
        public int Compare(Exam ex1, Exam ex2)
        {
            if (ex1.Date > ex2.Date)
                return 1;
            else if (ex1.Date < ex2.Date)
                return -1;
            else
                return 0;
        }
    }
}
