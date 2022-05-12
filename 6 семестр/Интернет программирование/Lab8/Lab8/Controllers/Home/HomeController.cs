using Microsoft.AspNetCore.Mvc;
using System.Xml.Linq;

namespace Lab8.Controllers.Home
{
    public class HomeController : Controller
    {
        IWebHostEnvironment _appEnvironment;

        public HomeController(IWebHostEnvironment appEnvironment)
        {
            _appEnvironment = appEnvironment;
        }

        public IActionResult Index()
        {
            string directory = _appEnvironment.WebRootPath;
            XDocument xDocument = XDocument.Load($"{directory}\\portfolio.xml");
            XElement projects = xDocument.Element("rootElement").Element("projects");

            return View(projects);
        }

        public IActionResult JsonObject()
        {
            string json = "{\r\n" +
                "\'projects\': [\r\n";
            string directory = _appEnvironment.WebRootPath;
            XDocument xDocument = XDocument.Load($"{directory}\\portfolio.xml");
            var projects = xDocument.Element("rootElement").Element("projects").Elements("project").ToArray();

            foreach (XElement project in projects)
            {
                json += "{\r\n" +
                    "\'attributes\': {\r\n" +
                    $"\'id\': \'{project.Attribute("id").Value}\',\r\n" +
                    $"\'year\': \'{project.Attribute("year").Value}\'\r\n" +
                    "},\r\n" +
                    "\'value\': {\r\n" +
                    $"\'title\': \'{project.Element("title").Value}\',\r\n" +
                    $"\'authors\': [\r\n";
                var autors = project.Element("authors").Elements("author").ToArray();
                foreach (XElement autor in autors)
                {
                    json += "{\r\n" +
                        $"\'country\': \'{autor.Attribute("country").Value}\',\r\n" +
                        $"\'name\': \'{autor.Value}\'\r\n" +
                        "}";
                    if(Array.IndexOf(autors, autor) != autors.Length - 1)
                    {
                        json += ",";
                    }
                    json += "\r\n";
                }
                json += "]\r\n" +
                    "}\r\n" +
                    "}";
                if(Array.IndexOf(projects, project) != projects.Length - 1)
                {
                    json += ",";
                }
                json += "\r\n";
            }
            json += "]\r\n" +
                "}";

            return new ObjectResult(json);
        }
    }
}
