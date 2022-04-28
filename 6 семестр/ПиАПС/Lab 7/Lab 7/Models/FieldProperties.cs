using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal class FieldProperties
    {
        public int Row { get; init; }
        public int Column { get; init; }
        public double BombDensity { get; init; }
        public int BombCount { 
            get
            {
                return (int)(Row * Column * BombDensity);
            }
        }
    }
}
