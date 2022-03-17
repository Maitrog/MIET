var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.UseStaticFiles();
app.MapGet("/", context => {
    context.Response.Redirect("/index.html");
    return Task.FromResult(0);
});

app.MapGet("/ajax_server", async (context) =>
{
    string? login = context.Request.Query["login"];
    string? password = context.Request.Query["password"];

    if (login == "lam" && password == "12345")
    {
        await context.Response.WriteAsync("Успешная авторизация");
    }
    else
    {
        await context.Response.WriteAsync("Ошибка авторизации");
    }
});

app.Run();
