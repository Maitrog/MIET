using Microsoft.AspNetCore.Mvc;

namespace BDZ.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}
