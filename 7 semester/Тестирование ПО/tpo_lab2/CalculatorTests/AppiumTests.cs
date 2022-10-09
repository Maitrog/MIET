using Microsoft.VisualStudio.TestTools.UnitTesting;
using OpenQA.Selenium.Appium;
using OpenQA.Selenium.Appium.Windows;
using OpenQA.Selenium.Remote;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CalculatorTests
{
    [TestClass]
    public class AppiumTests
    {
        protected const string WindowsApplicationDriverUrl = "http://127.0.0.1:4723";
        private const string CalculatorAppPath = @"C:\Users\Mihay\Documents\MIET\7 semester\Тестирование ПО\tpo_lab2\Calculator\bin\Debug\net4.7.2\Calculator.exe";

        public static WindowsDriver<WindowsElement> AppSession;
        private static WindowsElement result;

        [Obsolete]
        [ClassInitialize]
        public static void Setup(TestContext context)
        {
            var appiumOptions = new AppiumOptions();
            appiumOptions.AddAdditionalCapability("app", CalculatorAppPath);
            appiumOptions.AddAdditionalCapability("deviceName", "WindowsPC");
            AppSession = new WindowsDriver<WindowsElement>(new Uri(WindowsApplicationDriverUrl), appiumOptions);

            Assert.IsNotNull(AppSession);

            AppSession.Manage().Timeouts().ImplicitWait = TimeSpan.FromSeconds(1.5);

            result = AppSession.FindElementByAccessibilityId("result");
        }

        [ClassCleanup]
        public static void TearDown()
        {
            if (AppSession != null)
            {
                AppSession.Dispose();
                AppSession = null;
            }
        }

        [TestMethod]
        public void Addition()
        {
            AppSession.FindElementByAccessibilityId("firstArg").Clear();
            AppSession.FindElementByAccessibilityId("firstArg").SendKeys("1");

            AppSession.FindElementByAccessibilityId("secondArg").Clear();
            AppSession.FindElementByAccessibilityId("secondArg").SendKeys("7");

            AppSession.FindElementByAccessibilityId("plus").Click();

            Assert.AreEqual("8", GetCalculatorResultText());
        }

        [TestMethod]
        public void Subtraction()
        {
            AppSession.FindElementByAccessibilityId("firstArg").Clear();
            AppSession.FindElementByAccessibilityId("firstArg").SendKeys("2");
            AppSession.FindElementByAccessibilityId("firstArg").SendKeys("3");
            AppSession.FindElementByAccessibilityId("firstArg").SendKeys(".");
            AppSession.FindElementByAccessibilityId("firstArg").SendKeys("5");

            AppSession.FindElementByAccessibilityId("secondArg").Clear();
            AppSession.FindElementByAccessibilityId("secondArg").SendKeys("7");

            AppSession.FindElementByAccessibilityId("minus").Click();

            Assert.AreEqual("16.5", GetCalculatorResultText());
        }

        [TestMethod]
        public void Division()
        {
            AppSession.FindElementByAccessibilityId("firstArg").Clear();
            AppSession.FindElementByAccessibilityId("firstArg").SendKeys("4");

            AppSession.FindElementByAccessibilityId("secondArg").Clear();
            AppSession.FindElementByAccessibilityId("secondArg").SendKeys("2");

            AppSession.FindElementByAccessibilityId("divide").Click();

            Assert.AreEqual("2", GetCalculatorResultText());
        }

        [TestMethod]
        public void Multiply()
        {
            AppSession.FindElementByAccessibilityId("firstArg").Clear();
            AppSession.FindElementByAccessibilityId("firstArg").SendKeys("4");

            AppSession.FindElementByAccessibilityId("secondArg").Clear();
            AppSession.FindElementByAccessibilityId("secondArg").SendKeys("2");

            AppSession.FindElementByAccessibilityId("multiply").Click();

            Assert.AreEqual("8", GetCalculatorResultText());
        }

        [TestMethod]
        public void DivisionByZero()
        {
            AppSession.FindElementByAccessibilityId("firstArg").Clear();
            AppSession.FindElementByAccessibilityId("firstArg").SendKeys("4");

            AppSession.FindElementByAccessibilityId("secondArg").Clear();
            AppSession.FindElementByAccessibilityId("secondArg").SendKeys("0");

            AppSession.FindElementByAccessibilityId("divide").Click();

            Assert.AreEqual("Попытка деления на нуль.", GetCalculatorResultText());
        }

        [TestMethod]
        public void IncorrectInput()
        {
            AppSession.FindElementByAccessibilityId("firstArg").Clear();
            AppSession.FindElementByAccessibilityId("firstArg").SendKeys("fas");

            AppSession.FindElementByAccessibilityId("secondArg").Clear();
            AppSession.FindElementByAccessibilityId("secondArg").SendKeys("564");

            AppSession.FindElementByAccessibilityId("divide").Click();

            Assert.AreEqual("Некорректный ввод", GetCalculatorResultText());
        }

        private string GetCalculatorResultText()
        {
            return result.Text;
        }
    }
}
