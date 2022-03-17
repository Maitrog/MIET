var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.UseStaticFiles();
app.MapGet("/", context => {
    context.Response.Redirect("/index.html");
    return Task.FromResult(0);
});

app.Run();
