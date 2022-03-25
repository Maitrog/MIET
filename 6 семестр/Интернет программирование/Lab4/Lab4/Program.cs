using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;
using System.Security.Claims;

if (!File.Exists("users.json"))
{
    File.Create("users.json");
}
var users = new List<Person>();
var usersFromFile = JsonConvert.DeserializeObject<Person[]>(File.ReadAllText("users.json"));
if (usersFromFile != null)
{
    users = usersFromFile.ToList();
}

var builder = WebApplication.CreateBuilder();

builder.Services.AddAuthorization();
builder.Services.AddAuthentication(CookieAuthenticationDefaults.AuthenticationScheme)
    .AddCookie(options =>
    {
        options.LoginPath = new PathString("/login");
    });
builder.Services.AddControllersWithViews(options =>
{
    options.EnableEndpointRouting = true;
});
var app = builder.Build();

app.UseDefaultFiles();
app.UseStaticFiles();
app.UseRouting();

app.UseAuthentication();
app.UseAuthorization();

app.UseEndpoints(endpoints =>
{
    endpoints.MapControllerRoute(
        name: "default",
        pattern: "{controller=Home}/{action=Index}");
});

app.MapPost("/login", [ValidateAntiForgeryToken] async (HttpContext context, Person loginData) =>
{

    Person? person = users.FirstOrDefault(p => p.Login == loginData.Login && p.Password == loginData.Password);
    if (person is null)
    {
        return Results.Unauthorized();
    }

    var claims = new List<Claim>
            {
                new Claim(ClaimsIdentity.DefaultNameClaimType, person.Login)
            };
    ClaimsIdentity id = new ClaimsIdentity(claims, "ApplicationCookie", ClaimsIdentity.DefaultNameClaimType, ClaimsIdentity.DefaultRoleClaimType);
    await context.SignInAsync(CookieAuthenticationDefaults.AuthenticationScheme, new ClaimsPrincipal(id));
    var response = new
    {
        username = person.Login
    };

    return Results.Json(response);
});

app.MapPost("/logout", [Authorize] async (HttpContext context) =>
{
    await context.SignOutAsync(CookieAuthenticationDefaults.AuthenticationScheme);
    return Results.Ok("Logout success");
});

app.MapGet("/register", (context) =>
{
    context.Response.Redirect("/register.html");
    return Task.FromResult(0);
});

app.MapPost("/register", (Person registerData) =>
{
    if (users.FirstOrDefault(p => p.Login == registerData.Login) != null)
    {
        return Results.Unauthorized();
    }
    else
    {
        users.Add(registerData);
        File.WriteAllText("users.json", JsonConvert.SerializeObject(users));
        return Results.Ok("Register success");
    }
});

app.Run();

record class Person(string Login, string Password);

record class Image(string ImageName, byte[] Content, long Size);
