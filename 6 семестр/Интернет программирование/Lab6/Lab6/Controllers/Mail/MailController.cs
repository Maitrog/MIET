using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;

namespace Lab6.Controllers.Mail
{
    public class MailController : Controller
    {
        IWebHostEnvironment _appEnvironment;

        public MailController(IWebHostEnvironment environment)
        {
            _appEnvironment = environment;
        }

        [HttpGet]
        public IActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public async Task<IResult> Index(Models.MailData mail)
        {
            try
            {
                int incriment = await Models.Utils.addNewMailToDBAsync(_appEnvironment, mail);

                string result = "id:mail_" + incriment + "<hr>" + JsonConvert.SerializeObject(HttpContext.Request.Query) +
                                "<hr>" + JsonConvert.SerializeObject(mail);

                Console.WriteLine(JsonConvert.SerializeObject(HttpContext.Request.Query));

                return Results.Content(Models.Utils.makeHTML("<b>PUT Success</b>" + result), "text/html");
            }
            catch (Exception ex)
            {
                Console.WriteLine("[ERROR] " + ex.Message + "\n" + ex.StackTrace);
                return Results.BadRequest();
            }
        }
    }
}
