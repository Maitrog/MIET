using lab6.Enums;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab6.Tags
{
    public class ColumnTag : BasedTag
    {
        public Valign Valign { get; set; } = Valign.Top;
        public Halign Halign { get; set; } = Halign.Left;
        public int TextColor { get; set; } = 15;
        public int BgColor { get; set; } = 0;

        public ColumnTag(BasedTag? parent, int? width = null, int? height = null) : base(parent, width, height)
        {
        }
    }
}
