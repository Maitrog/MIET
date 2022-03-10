using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_2.Builder
{
    internal sealed class Station
    {
        private IBuilder? _builder;
        public IBuilder Builder
        {
            set { _builder = value; }
        }

        public void CreateBoard()
        {
            _builder!.BuildDriver();
            _builder.BuildPassenger();
        }
    }
}
