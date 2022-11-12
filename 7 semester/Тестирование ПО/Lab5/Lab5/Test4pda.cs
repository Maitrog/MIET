using Microsoft.VisualStudio.TestTools.UnitTesting;
using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;
using System.Threading;

namespace Lab5
{
    [TestClass]
    public class Test4pda
    {
        [TestMethod]
        public void FailedSearch()
        {
            var driver = new ChromeDriver();

            driver.Navigate().GoToUrl("https://4pda.to");

            driver.FindElement(By.Id("search-open")).Click();

            var searchInput = driver.FindElement(By.ClassName("search-input-mobile"));

            searchInput.Click();
            searchInput.SendKeys("sfasfasfas");

            driver.FindElement(By.ClassName("search-submit-mobile")).Click();

            var count = driver.FindElement(By.ClassName("s-count")).FindElement(By.TagName("strong"));

            Assert.AreEqual(count.Text, "0");
            driver.Quit();
        }

        [TestMethod]
        public void Search()
        {
            var driver = new ChromeDriver();

            driver.Navigate().GoToUrl("https://4pda.to");

            driver.FindElement(By.Id("search-open")).Click();

            var searchInput = driver.FindElement(By.ClassName("search-input-mobile"));

            searchInput.Click();
            searchInput.SendKeys("rtx 4090");

            driver.FindElement(By.ClassName("search-submit-mobile")).Click();

            var count = driver.FindElement(By.ClassName("s-count")).FindElement(By.TagName("strong"));

            Assert.AreNotEqual(count.Text, "0");
            driver.Quit();
        }

        [TestMethod]
        public void FailedRegistration_ErrorCaptcha()
        {
            var driver = new ChromeDriver();

            driver.Navigate().GoToUrl("https://4pda.to/forum");

            driver.FindElement(By.PartialLinkText("Регистрация")).Click();

            driver.FindElement(By.Id("reg-term-1")).Click();

            driver.FindElement(By.Id("reg-term-2")).Click();

            driver.FindElement(By.Id("reg")).FindElement(By.ClassName("input-wrap")).Click();

            var login = driver.FindElement(By.Name("login"));
            login.SendKeys("aspdfh14323513456");

            var password = driver.FindElement(By.Name("password"));
            password.SendKeys("askljdfhasugfh");

            var password2 = driver.FindElement(By.Name("password2"));
            password2.SendKeys("askljdfhasugfh");
            
            var email = driver.FindElement(By.Name("email"));
            email.SendKeys("asf@mail.ru");
            
            var captcha = driver.FindElement(By.Name("captcha"));
            captcha.SendKeys("3333");

            driver.FindElements(By.ClassName("input-wrap"))[5].Click();

            var title = driver.FindElement(By.ClassName("error-content")).FindElement(By.ClassName("title"));

            var error = driver.FindElement(By.ClassName("error-content"))
                .FindElement(By.ClassName("errors-list"))
                .FindElement(By.TagName("li"));

            Assert.AreEqual(title.Text, "Ошибка:");

            Assert.AreEqual(error.Text, "Введено неверное число с картинки. Попробуйте ещё раз.");

            driver.Quit();
        }

        [TestMethod]
        public void Pool()
        {
            var driver = new ChromeDriver();

            driver.Navigate().GoToUrl("https://4pda.to/2022/10/03/404571/opros_gotovy_li_vy_peresest_na_linux/");

            Thread.Sleep(100);

            var pool = driver.FindElement(By.ClassName("diagram-box"));

            pool.FindElement(By.ClassName("poll-list")).FindElement(By.TagName("li")).Click();

            driver.Quit();
        }
    }
}