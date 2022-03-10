using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_1.AbstractFactory
{
    internal abstract class Driver
    {
        protected string _license = string.Empty;
        public string License
        {
            get
            {
                return _license;
            }
            protected internal set
            {
                if (value != null)
                {
                    _license = value;
                }
            }
        }
    }
}
