using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab6.Tags
{
    public abstract class BasedTag
    {
        public BasedTag? Parent { get; init; }
        public List<BasedTag> Children { get; } = new();
        public int Width { get; init; } = 80;
        public int Height { get; init; } = 24;

        public string Text { get; set; } = "";

        public BasedTag(BasedTag? parent, int? width = null, int? height = null)
        {
            Parent = parent;
            if (width != null)
            {
                Width = width.Value;
            }
            if (height != null)
            {
                Height = height.Value;
            }
        }
    }
}
