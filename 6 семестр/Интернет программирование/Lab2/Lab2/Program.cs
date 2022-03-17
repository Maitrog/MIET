using Microsoft.Extensions.FileProviders;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.UseStaticFiles();
app.MapGet("/", app =>  {
    app.Response.Redirect("/index.html");
    return Task.FromResult(0);
});

app.Run();