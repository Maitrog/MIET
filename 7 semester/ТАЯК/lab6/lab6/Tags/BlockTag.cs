using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab6.Tags
{
    public class BlockTag : BasedTag
    {
        public int Columns { get; set; }
        public int Rows { get; set; }

        public BlockTag() : base(null)
        { }

        public BlockTag(BasedTag? parent, int? width = null, int? height = null) : base(parent, width, height)
        {
        }
    }
}
