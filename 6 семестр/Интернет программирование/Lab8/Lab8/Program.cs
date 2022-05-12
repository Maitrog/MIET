using System.Text;
using System.Xml;
using System.Xml.Linq;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddControllersWithViews(options =>
{
    options.EnableEndpointRouting = true;
});

var app = builder.Build();

app.UseStaticFiles();

app.UseRouting();
app.UseEndpoints(endpoints =>
{
    endpoints.MapControllerRoute(
        name: "default",
        pattern: "{controller=Home}/{action=Index}");
});

app.Run();
