using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Diagnostics;


namespace Lab6
{
    class TridiagonalMatrix
    {
        public int Dimension { get; set; }
        private List<double> mainDiag;
        private List<double> aboveMainDiag;
        private List<double> belowMainDiag;
        public TridiagonalMatrix(int _dim)
        {
            if (_dim < 2)
                throw new Exception("Dimension must be greater than 1");
            Dimension = _dim;
            mainDiag = new List<double>(_dim);
            aboveMainDiag = new List<double>(_dim - 1);
            belowMainDiag = new List<double>(_dim - 1);
            for (int i = 0; i < Dimension; i++)
            {
                mainDiag.Add(i);
            }
            for (int i = 0; i < Dimension - 1; i++)
            {
                aboveMainDiag.Add(i);
                belowMainDiag.Add(i);
            }
        }

        public TridiagonalMatrix(int _dim, params double[] _diag)
        {
            if (_dim < 2)
                throw new Exception("Dimension must be greater than 1");
            Dimension = _dim;

            if (_diag.Length != _dim * 3 - 2)
                throw new Exception("Incorrect matrix assignment");

            aboveMainDiag = new List<double>(_dim - 1);
            for (int i = 0; i < _dim - 1; i++)
            {
                aboveMainDiag.Add(_diag[i]);
            }
            mainDiag = new List<double>(_dim);
            for(int i = _dim - 1; i < _dim * 2 - 1; i++)
            {
                mainDiag.Add(_diag[i]);
            }
            belowMainDiag = new List<double>(_dim - 1);
            for(int i = _dim * 2 - 1; i < _dim * 3 - 2; i++)
            {
                belowMainDiag.Add(_diag[i]);
            }
        }

        public TridiagonalMatrix(int _dim, double[] _aboveMainDiag, double[] _mainDiag, double[] _belowMainDiag)
        {
            if (_dim < 3)
                throw new Exception("Dimension must be greater than 2");
            Dimension = _dim;

            if (_aboveMainDiag.Length != _dim - 1 || _mainDiag.Length != _dim || _belowMainDiag.Length != _dim - 1)
                throw new Exception("Incorrect matrix assignment");

            foreach (double i in _aboveMainDiag)
                aboveMainDiag.Add(i);
            foreach (double i in _mainDiag)
                mainDiag.Add(i);
            foreach (double i in _belowMainDiag)
                belowMainDiag.Add(i);
        }

        public double[] Solve(params double[] _f)
        {
            if (_f.Length != Dimension)
                throw new Exception("");
            List<double> beta = new List<double>(Dimension);
            List<double> gamma = new List<double>(Dimension);

            beta.Add(aboveMainDiag[0] / mainDiag[0]);
            gamma.Add(_f[0] / mainDiag[0]);

            for(int i = 1; i < Dimension - 1; i++)
            {
                beta.Add(aboveMainDiag[i] / (mainDiag[i] - beta[i - 1] * belowMainDiag[i - 1]));
                gamma.Add((_f[i] - belowMainDiag[i - 1] * gamma[i - 1]) / (mainDiag[i] - beta[i - 1] * belowMainDiag[i - 1]));
            }
            gamma.Add((_f[Dimension - 1] - belowMainDiag[Dimension - 2] * gamma[Dimension - 2]) / (mainDiag[Dimension - 1] - beta[Dimension - 2] * belowMainDiag[Dimension - 2]));

            double[] solve = new double[Dimension];
            solve[Dimension - 1] = gamma[Dimension - 1];
            for(int i = Dimension-2; i >=0; i--)
            {
                solve[i] = gamma[i] - beta[i] * solve[i + 1];
            }
            
            return solve;
        }

        public override string ToString()
        {
            string str = "";
            str += mainDiag[0] + "\t" + aboveMainDiag[0] + "\t";
            for (int i = 0; i < Dimension - 2; i++)
                str += 0 + "\t";
            str += "\n";
            for (int i = 1; i < Dimension - 1; i++)
            {
                for (int j = 0; j < Dimension; j++)
                {
                    if (j == i - 1)
                    {
                        str += belowMainDiag[j] + "\t" + mainDiag[j + 1] + "\t" + aboveMainDiag[j + 1] + "\t";
                        j += 2;
                    }
                    else
                        str += 0 + "\t";
                }
                str += "\n";
            }
            for (int i = 0; i < Dimension - 2; i++)
                str += 0 + "\t";
            str += belowMainDiag[Dimension - 2] + "\t" + mainDiag[Dimension - 1];
            return str;
        }
    }
}
