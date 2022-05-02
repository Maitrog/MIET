using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7.Models
{
    internal class Field
    {
        private readonly CellCreator _cellCreator;
        public FieldProperties Properties { get; init; }
        public BaseCell[,] Cells { get; init; }

        public Field()
        {
            Properties = new FieldProperties() { Row = 15, Column = 20, BombDensity = 0.13 };
            _cellCreator = new CellCreator();
            Cells = new BaseCell[Properties.Row, Properties.Column];
            CreateField();
        }

        public Field(FieldProperties properties)
        {
            Properties = properties;
            _cellCreator = new CellCreator();
            Cells = new BaseCell[Properties.Row, Properties.Column];
            CreateField();
        }
        private void CreateField()
        {
            for (int i = 0; i < Properties.Row; i++)
            {
                for (int j = 0; j < Properties.Column; j++)
                {
                    Cells[i, j] = _cellCreator.CreateCell();
                }
            }
        }

        public void Clear()
        {
            Array.Clear(Cells);
            CreateField();
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
                    IBomb bomb = new BombCell();
                    Cells[cellNumber / Properties.Column, cellNumber % Properties.Column] = bomb.GetBomb();
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
