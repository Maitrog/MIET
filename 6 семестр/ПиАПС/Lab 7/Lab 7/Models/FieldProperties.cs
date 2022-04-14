using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal class FieldProperties
    {
        public int Row { get; set; }
        public int Column { get; set; }
        public double BombDensity { get; set; }
        public int BombCount { 
            get
            {
                return (int)(Row * Column * BombDensity);
            }
        }
    }
}
