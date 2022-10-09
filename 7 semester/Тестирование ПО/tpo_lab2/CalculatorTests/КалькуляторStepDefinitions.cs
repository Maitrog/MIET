using Calculator;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using TechTalk.SpecFlow;

namespace CalculatorTests
{
    [Binding]
    public class КалькуляторStepDefinitions
    {
        MainWindow mainWindow;
        [Given(@"Я открыл окно кулькулятора")]
        public void GivenЯОткрылОкноКулькулятора()
        {
            mainWindow = new MainWindow();
        }

        [Given(@"я ввел (.*) в окно первого аргумента")]
        public void GivenЯВвелВОкноПервогоАргумента(string p0)
        {
            mainWindow.FirstArgument = p0.ToString();
        }

        [Given(@"я ввел (.*) в окно второго аргумента")]
        public void GivenЯВвелВОкноВторогоАргумента(string p0)
        {
            mainWindow.SecondArgument = p0.ToString();
        }

        [When(@"я нажимаю кнопку Плюс")]
        public void WhenЯНажимаюКнопкуПлюс()
        {
            mainWindow.plus_Click(null, null);
        }

        [Then(@"в окне результата появляется (.*)")]
        public void ThenВОкнеРезультатаПоявляется(string p0)
        {
            Assert.AreEqual(mainWindow.Result, p0);
        }

        [When(@"я нажимаю кнопку Минус")]
        public void WhenЯНажимаюКнопкуМинус()
        {
            mainWindow.minus_Click(null, null);
        }

        [When(@"я нажимаю кнопку Умножить")]
        public void WhenЯНажимаюКнопкуУмножить()
        {
            mainWindow.multiply_Click(null, null);
        }

        [When(@"я нажимаю кнопку Делить")]
        public void WhenЯНажимаюКнопкуДелить()
        {
            mainWindow.divide_Click(null, null);
        }

        [Then(@"вызвыно исключение деления на ноль")]
        public void ThenВызвыноИсключениеДеленияНаНоль()
        {
            Assert.AreEqual(mainWindow.Result, "Attempted to divide by zero.");
        }

        [Then(@"вызвыно исключение некорректного ввода")]
        public void ThenВызвыноИсключениеНекорректногоВвода()
        {
            Assert.AreEqual(mainWindow.Result, "Некорректный ввод");
        }

    }
}
