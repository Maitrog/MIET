using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace Lab4.Controllers.Photo
{
    public class PhotoController : Controller
    {
        IWebHostEnvironment _appEnvironment;

        public PhotoController(IWebHostEnvironment webHostEnvironment)
        {
            _appEnvironment = webHostEnvironment;
        }
        [HttpGet]
        [Authorize]
        public IActionResult Photo()
        {
            return View();
        }

        [HttpPost]
        public async Task<IActionResult> Photo(IFormFile userPhoto)
        {
            if (!Directory.Exists("/Images"))
            {
                Directory.CreateDirectory(_appEnvironment.WebRootPath + "/Images");
            }
            if(userPhoto != null)
            {
                string path = "/Images/" + userPhoto.FileName;
                using(var fs = new FileStream(_appEnvironment.WebRootPath + path, FileMode.Create))
                {
                    await userPhoto.CopyToAsync(fs);
                }
            }
            return RedirectToAction("Photo");
        }
    }
}
