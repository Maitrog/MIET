using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_4
{
    public struct BlowfishCtx
    {
        public ulong[] p = new ulong[18];
        public ulong[,] sbox = new ulong[4, 256];

        public BlowfishCtx(ulong[] p, ulong[,] sbox)
        {
            this.p = p;
            this.sbox = sbox;
        }
    }
}
