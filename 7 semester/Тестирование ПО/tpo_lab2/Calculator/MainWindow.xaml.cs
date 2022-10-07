using Calculator.Intefaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Calculator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, ICalculatorPresenter, ICalculatorView, ICalculator
    {
        public string Result
        {
            get { return result.Text; }
        }
        public string FirstArgument
        {
            get
            {
                return firstArg.Text;
            }
            set
            {
                firstArg.Text = value;
            }
        }

        public string SecondArgument
        {
            get
            {
                return secondArg.Text;
            }
            set
            {
                secondArg.Text = value;
            }
        }

        public MainWindow()
        {
            InitializeComponent();
        }

        public void minus_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                OnMinusClicked();
            }
            catch (Exception ex)
            {
                DisplayError(ex.Message);
            }
        }

        public void plus_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                OnPlusClicked();
            }
            catch (Exception ex)
            {
                DisplayError(ex.Message);
            }
        }

        public void divide_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                OnDivideClicked();
            }
            catch (Exception ex)
            {
                DisplayError(ex.Message);
            }
        }

        public void multiply_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                OnMultiplyClicked();
            }
            catch (Exception ex)
            {
                DisplayError(ex.Message);
            }
        }

        public void OnPlusClicked()
        {
            if (double.TryParse(GetFirstArgumentAsString(), out var firstArg) &&
                double.TryParse(GetSecondArgumentAsString(), out var secondArg))
            {
                var result = Sum(firstArg, secondArg);
                PrintResult(result);
            }
            else
            {
                throw new Exception("Некорректный ввод");
            }
        }

        public void OnMinusClicked()
        {

            if (double.TryParse(GetFirstArgumentAsString(), out var firstArg) &&
                double.TryParse(GetSecondArgumentAsString(), out var secondArg))
            {
                var result = Subtract(firstArg, secondArg);
                PrintResult(result);
            }
            else
            {
                throw new Exception("Некорректный ввод");
            }
        }

        public void OnDivideClicked()
        {
            if (double.TryParse(GetFirstArgumentAsString(), out var firstArg) &&
                double.TryParse(GetSecondArgumentAsString(), out var secondArg))
            {
                var result = Divide(firstArg, secondArg);
                PrintResult(result);
            }
            else
            {
                throw new Exception("Некорректный ввод");
            }
        }

        public void OnMultiplyClicked()
        {
            if (double.TryParse(GetFirstArgumentAsString(), out var firstArg) &&
                double.TryParse(GetSecondArgumentAsString(), out var secondArg))
            {
                var result = Multiply(firstArg, secondArg);
                PrintResult(result);
            }
            else
            {
                throw new Exception("Некорректный ввод");
            }
        }

        public double Sum(double a, double b)
        {
            return a + b;
        }

        public double Subtract(double a, double b)
        {
            return a - b;
        }

        public double Multiply(double a, double b)
        {
            return a * b;
        }

        public double Divide(double a, double b)
        {
            return a / b;
        }

        public void PrintResult(double result)
        {
            this.result.Text = result.ToString();
        }

        public void DisplayError(string message)
        {
            result.Text = message;
        }

        public string GetFirstArgumentAsString()
        {
            var arg = firstArg.Text;
            return arg;
        }

        public string GetSecondArgumentAsString()
        {
            var arg = secondArg.Text;
            return arg;
        }
    }
}
