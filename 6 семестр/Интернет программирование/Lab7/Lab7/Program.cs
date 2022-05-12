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

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddCors(options =>
{
    options.AddPolicy("CORSPolicy", builder =>
    {
        builder
        .AllowAnyHeader()
        .AllowAnyMethod()
        .AllowCredentials()
        .WithOrigins("http://localhost:3000", "https://appname.azurestaticapps.net");
    });
});
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

builder.Services.AddAuthorization();
builder.Services.AddAuthentication(CookieAuthenticationDefaults.AuthenticationScheme)
    .AddCookie(CookieAuthenticationDefaults.AuthenticationScheme, options =>
    {
        options.LoginPath = new PathString("/login");
        options.Cookie.Name = "UserAuthorize";
        options.Events.OnRedirectToLogin = (context) =>
        {
            context.Response.StatusCode = StatusCodes.Status401Unauthorized;
            return Task.CompletedTask;
        };
        options.Cookie.HttpOnly = true;
        options.Cookie.SameSite = Microsoft.AspNetCore.Http.SameSiteMode.None;
    });

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

app.UseCors("CORSPolicy");

app.UseCookiePolicy(
    new CookiePolicyOptions
    {
        Secure = CookieSecurePolicy.Always
    });

app.UseAuthentication();
app.UseAuthorization();

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

app.MapPost("/logout", [Authorize(AuthenticationSchemes = CookieAuthenticationDefaults.AuthenticationScheme)] async (HttpContext context) =>
{
    await context.SignOutAsync(CookieAuthenticationDefaults.AuthenticationScheme);
    return Results.Ok("Logout success");
});

app.MapPost("/register", (Person registerData) =>
{
    if (users.FirstOrDefault(p => p.Login == registerData.Login) != null)
    {
        return Results.BadRequest();
    }
    else
    {
        users.Add(registerData);
        File.WriteAllText("users.json", JsonConvert.SerializeObject(users));
        return Results.Ok("Register success");
    }
});

app.MapPost("/gallery", async (HttpContext context) =>
{
    var form = context.Request.Form;
    ImageDTO image = new ImageDTO(form.Files[0].FileName, form.Files[0]);
    string dir = Directory.GetCurrentDirectory() + "/Images";
    if (!Directory.Exists(dir))
    {
        Directory.CreateDirectory(dir);
    }
    if (image.file != null)
    {
        string path = dir + "/" + image.file.FileName;
        using (var fs = new FileStream(path, FileMode.Create))
        {
            await image.file.CopyToAsync(fs);
        }
        return Results.Ok();
    }
    return Results.BadRequest();
});

app.MapGet("/gallery/{fileName}", (string fileName) =>
{
    if (!string.IsNullOrEmpty(fileName))
    {
        string path = Directory.GetCurrentDirectory() + "/Images/" + fileName;
        if (File.Exists(path))
        {
            return Results.File(path, "image/jpeg", enableRangeProcessing: true);
        }
        return Results.NotFound();
    }
    return Results.BadRequest();
});

app.MapGet("/gallery", () =>
{
    string path = Directory.GetCurrentDirectory() + "/Images";
    if (!Directory.Exists(path))
    {
        return Results.Ok();
    }
    var files = Directory.GetFiles(path);
    for (int i = 0; i < files.Length; i++)
    {
        files[i] = files[i].Split("\\").Last();
    }
    return Results.Json(files);

});

app.Run();

record class Person(string Login, string Password);

record class Image(string ImageName, byte[] Content, long Size);

record class ImageDTO(string ImageName, IFormFile file);