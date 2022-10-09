using Calculator;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

namespace CalculatorTests
{
    [TestClass]
    public class UnitTest1
    {
        MainWindow mainWindow = new MainWindow();

        [TestMethod]
        public void TestSum()
        {
            var res = mainWindow.Sum(2.2, 5.1);

            Assert.AreEqual(res, 7.3);
        }

        [TestMethod]
        public void TestSubtract()
        {
            var res = mainWindow.Subtract(11, 1.6);

            Assert.AreEqual(res, 9.4);
        }

        [TestMethod]
        public void TestDivide()
        {
            var res = mainWindow.Divide(3, 4);

            Assert.AreEqual(res, 0.75);
        }

        [TestMethod]
        public void TestZeroDivide()
        {
            Assert.ThrowsException<DivideByZeroException>(() => mainWindow.Divide(3, 0));
        }

        [TestMethod]
        public void TestMultiply()
        {
            var res = mainWindow.Multiply(2, 5);

            Assert.AreEqual(res, 10);
        }

        [TestMethod]
        public void TestGetFirstArgumentAsString()
        {
            mainWindow.FirstArgument = "11";
            var arg = mainWindow.GetFirstArgumentAsString();

            Assert.AreEqual(arg, "11");

            mainWindow.FirstArgument = "";
        }

        [TestMethod]
        public void TestGetSecondArgumentAsString()
        {
            mainWindow.SecondArgument = "15";
            var arg = mainWindow.GetSecondArgumentAsString();

            Assert.AreEqual(arg, "15");

            mainWindow.SecondArgument = "";
        }

        [TestMethod]
        public void TestDisplayError_1()
        {
            mainWindow.FirstArgument = "11";
            mainWindow.SecondArgument = "ff";
            mainWindow.minus_Click(null, null);

            Assert.AreEqual(mainWindow.Result, "Некорректный ввод");

            mainWindow.FirstArgument = "";
            mainWindow.SecondArgument = "";
        }

        [TestMethod]
        public void TestDisplayError_2()
        {
            mainWindow.FirstArgument = "s";
            mainWindow.SecondArgument = "3";
            mainWindow.minus_Click(null, null);

            Assert.AreEqual(mainWindow.Result, "Некорректный ввод");

            mainWindow.FirstArgument = "";
            mainWindow.SecondArgument = "";
        }

        [TestMethod]
        public void TestDisplayError_3()
        {
            mainWindow.FirstArgument = "11";
            mainWindow.SecondArgument = "ff";
            mainWindow.plus_Click(null, null);

            Assert.AreEqual(mainWindow.Result, "Некорректный ввод");

            mainWindow.FirstArgument = "";
            mainWindow.SecondArgument = "";
        }

        [TestMethod]
        public void TestDisplayError_4()
        {
            mainWindow.FirstArgument = "s";
            mainWindow.SecondArgument = "3";
            mainWindow.plus_Click(null, null);

            Assert.AreEqual(mainWindow.Result, "Некорректный ввод");

            mainWindow.FirstArgument = "";
            mainWindow.SecondArgument = "";
        }

        [TestMethod]
        public void TestDisplayError_5()
        {
            mainWindow.FirstArgument = "11";
            mainWindow.SecondArgument = "ff";
            mainWindow.divide_Click(null, null);

            Assert.AreEqual(mainWindow.Result, "Некорректный ввод");

            mainWindow.FirstArgument = "";
            mainWindow.SecondArgument = "";
        }

        [TestMethod]
        public void TestDisplayError_6()
        {
            mainWindow.FirstArgument = "s";
            mainWindow.SecondArgument = "3";
            mainWindow.divide_Click(null, null);

            Assert.AreEqual(mainWindow.Result, "Некорректный ввод");

            mainWindow.FirstArgument = "";
            mainWindow.SecondArgument = "";
        }

        [TestMethod]
        public void TestDisplayError_7()
        {
            mainWindow.FirstArgument = "11";
            mainWindow.SecondArgument = "ff";
            mainWindow.multiply_Click(null, null);

            Assert.AreEqual(mainWindow.Result, "Некорректный ввод");

            mainWindow.FirstArgument = "";
            mainWindow.SecondArgument = "";
        }

        [TestMethod]
        public void TestDisplayError_8()
        {
            mainWindow.FirstArgument = "s";
            mainWindow.SecondArgument = "3";
            mainWindow.multiply_Click(null, null);

            Assert.AreEqual(mainWindow.Result, "Некорректный ввод");

            mainWindow.FirstArgument = "";
            mainWindow.SecondArgument = "";
        }
    }
}
