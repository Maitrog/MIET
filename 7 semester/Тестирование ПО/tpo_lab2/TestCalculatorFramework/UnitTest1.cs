using Calculator;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;


namespace TestCalculatorFramework
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestSum()
        {
            MainWindow mainWindow = new MainWindow();
            mainWindow.FirstArgument = "2";
            mainWindow.SecondArgument = "5";
            mainWindow.plus_Click(null, null);

            Assert.AreEqual(mainWindow.Result, "7");
        }

        [TestMethod]
        public void TestSubtract()
        {
            MainWindow mainWindow = new MainWindow();
            mainWindow.FirstArgument = "2";
            mainWindow.SecondArgument = "5";
            mainWindow.minus_Click(null, null);

            Assert.AreEqual(mainWindow.Result, "-3");
        }

        [TestMethod]
        public void TestDivide()
        {
            MainWindow mainWindow = new MainWindow();
            mainWindow.FirstArgument = "2";
            mainWindow.SecondArgument = "2";
            mainWindow.divide_Click(null, null);

            Assert.AreEqual(mainWindow.Result, "1");
        }

        [TestMethod]
        public void TestMultiply()
        {
            MainWindow mainWindow = new MainWindow();
            mainWindow.FirstArgument = "2";
            mainWindow.SecondArgument = "5";
            mainWindow.multiply_Click(null, null);

            Assert.AreEqual(mainWindow.Result, "10");
        }

        [TestMethod]
        public void TestGetFirstArgumentAsString()
        {
            MainWindow mainWindow = new MainWindow();
            mainWindow.FirstArgument = "11";
            var arg = mainWindow.GetFirstArgumentAsString();

            Assert.AreEqual(arg, "11");
        }

        [TestMethod]
        public void TestGetSecondArgumentAsString()
        {
            MainWindow mainWindow = new MainWindow();
            mainWindow.SecondArgument = "15";
            var arg = mainWindow.GetSecondArgumentAsString();

            Assert.AreEqual(arg, "15");
        }

        [TestMethod]
        public void TestDisplayError()
        {
            MainWindow mainWindow = new MainWindow();
            mainWindow.FirstArgument = "11";
            mainWindow.SecondArgument = "ff";
            mainWindow.minus_Click(null, null);

            Assert.AreEqual(mainWindow.Result, "Некорректный ввод");
        }
    }
}
