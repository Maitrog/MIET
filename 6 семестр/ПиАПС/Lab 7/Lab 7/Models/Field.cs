using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal class Field
    {
        public FieldProperties Properties { get; init; }
        public Cell[,] Cells { get; init; }
        readonly IBomb _bomb = new BombCell();

        public Field()
        {
            Properties = new FieldProperties() { Row = 15, Column = 20, BombDensity = 0.13 };
            Cells = new Cell[Properties.Row, Properties.Column];
            Cell cell = new();
            for (int i = 0; i < Properties.Row; i++)
            {
                for (int j = 0; j < Properties.Column; j++)
                {
                    Cells[i, j] = (Cell)cell.Clone();
                }
            }
        }

        public Field(FieldProperties properties)
        {
            Properties = properties;
            Cells = new Cell[Properties.Row, Properties.Column];
            for (int i = 0; i < Properties.Row; i++)
            {
                for (int j = 0; j < Properties.Column; j++)
                {
                    Cells[i, j] = new Cell();
                }
            }
        }

        public void Clear()
        {
            for (int i = 0; i < Properties.Row; i++)
            {
                for (int j = 0; j < Properties.Column; j++)
                {
                    Cells[i, j].Clear();
                }
            }
        }

        public void FillBomb()
        {
            Random rnd = new Random();
            for (int i = 0; i < Properties.BombCount; i++)
            {
                int cellNumber = rnd.Next(0, Properties.Row * Properties.Column);
                if (Cells[cellNumber / Properties.Column, cellNumber % Properties.Column].IsBomb)
                {
                    i--;
                }
                else
                {
                    Cells[cellNumber / Properties.Column, cellNumber % Properties.Column] = _bomb.GetBomb();
                }
            }
        }

        public void SubscribeObservers(int i, int j)
        {
            if (i != 0)
            {
                Cells[i, j].Attach(Cells[i - 1, j]);
            }
            if (i != Properties.Row - 1)
            {
                Cells[i, j].Attach(Cells[i + 1, j]);
            }
            if (j != 0)
            {
                Cells[i, j].Attach(Cells[i, j - 1]);
            }
            if (j != Properties.Column - 1)
            {
                Cells[i, j].Attach(Cells[i, j + 1]);
            }
            if (i != 0 && j != 0)
            {
                Cells[i, j].Attach(Cells[i - 1, j - 1]);
            }
            if (i != Properties.Row - 1 && j != 0)
            {
                Cells[i, j].Attach(Cells[i + 1, j - 1]);
            }
            if (i != 0 && j != Properties.Column - 1)
            {
                Cells[i, j].Attach(Cells[i - 1, j + 1]);
            }
            if (i != Properties.Row - 1 && j != Properties.Column - 1)
            {
                Cells[i, j].Attach(Cells[i + 1, j + 1]);
            }
        }

        public bool IsWin()
        {
            for (int i = 0; i < Properties.Row; i++)
            {
                for (int j = 0; j < Properties.Column; j++)
                {
                    if (!Cells[i, j].IsOpen && !Cells[i, j].IsBomb)
                    {
                        return false;
                    }
                }
            }
            return true;
        }
    }
}
