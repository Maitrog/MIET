using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_2.Builder
{
    internal interface IBuilder
    {
        public void BuildDriver();
        public void CheckProtected();
        public void BuildPassenger();
        public void Reset();
        public Board GetBoard();
    }
}
