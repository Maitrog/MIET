using Lab6.Models;
using Newtonsoft.Json;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();
builder.Services.AddControllersWithViews(options =>
{
    options.EnableEndpointRouting = true;
});

var app = builder.Build();

if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

app.UseRouting();

app.UseEndpoints(endpoints =>
{
    endpoints.MapControllerRoute(
        name: "default",
        pattern: "{controller=Home}/{action=Index}");
});

app.MapGet("/getMailList", (HttpContext context) =>
{
    string result;
    Console.WriteLine(context.Request.Query.ToString());
    var action = context.Request.Query["action"];
    switch (action)
    {
        case "filter":
            Console.WriteLine(context.Request.Query["filter"]);
            result = Utils.makeFilter(context.Request.Query["filter"]);
            break;
        default:
            result = Utils.getAllData();
            break;
    }
    return Results.Content(Utils.makeHTML(result), "text/html");
});

app.MapGet("/addMail", (HttpContext context) =>
{
    string result = "<hr>" + JsonConvert.SerializeObject(context.Request.Query) + "<hr>";
    Console.WriteLine(JsonConvert.SerializeObject(context.Request.Query));

    return Results.Content(Utils.makeHTML("<b>GET Success</b>" + result), "text/html");
});

app.MapPut("/addMail/{mail}", async (HttpContext context, IWebHostEnvironment appEnvironment, MailData mail) =>
{
    try
    {
        int incriment = await Utils.addNewMailToDBAsync(appEnvironment,mail);

        string result = "id:mail_" + incriment + "<hr>" + JsonConvert.SerializeObject(context.Request.Query) +
                        "<hr>" + JsonConvert.SerializeObject(mail);

        Console.WriteLine(JsonConvert.SerializeObject(context.Request.Query));

        return Results.Content(Utils.makeHTML("<b>PUT Success</b>" + result), "text/html");
    }
    catch (Exception ex)
    {
        Console.WriteLine("[ERROR] " + ex.Message + "\n" + ex.StackTrace);
        return Results.BadRequest();
    }
});

app.MapDelete("/deleteMail/{id}", (HttpContext context, string id) =>
{
    try
    {
        List<Mail> mailList = JsonConvert.DeserializeObject<Mail[]>(Utils.getAllData()).ToList();
        string result = "";

        foreach (Mail mail in mailList)
        {
            if (mail.Id == id)
            {
                result = mail.Id;
                mailList.Remove(mail);
                break;
            }
        }
        Utils.saveAllData(JsonConvert.SerializeObject(mailList.ToArray()));

        Console.WriteLine(JsonConvert.SerializeObject(context.Request.Query));

        return Results.Content(Utils.makeHTML("<b>DELETE Success</b>" + result), "text/html");
    }
    catch (Exception ex)
    {
        Console.WriteLine("[ERROR] " + ex.Message + "\n" + ex.StackTrace);
        return Results.BadRequest();
    }
});

app.MapPut("/addMails/{mails}", async (HttpContext context, IWebHostEnvironment appEnvironment, MailData[] mails) =>
{
    try
    {
        string result = "";
        foreach (MailData mail in mails)
        {
            int incriment = await Utils.addNewMailToDBAsync(appEnvironment, mail);

            result += "id:mail_" + incriment + "<hr>" + JsonConvert.SerializeObject(context.Request.Query) +
                            "<hr>" + JsonConvert.SerializeObject(mail) + "\n";
        }

        Console.WriteLine(JsonConvert.SerializeObject(context.Request.Query));

        return Results.Content(Utils.makeHTML("<b>PUT Success</b>" + result), "text/html");
    }
    catch (Exception ex)
    {
        Console.WriteLine("[ERROR] " + ex.Message + "\n" + ex.StackTrace);
        return Results.BadRequest();
    }
});

app.MapPost("/addMails/{mails}", async (HttpContext context, IWebHostEnvironment appEnvironment, MailData[] mails) =>
{
    try
    {
        string result = "";
        foreach (MailData mail in mails)
        {
            int incriment = await Utils.addNewMailToDBAsync(appEnvironment, mail);

            result += "id:mail_" + incriment + "<hr>" + JsonConvert.SerializeObject(context.Request.Query) +
                            "<hr>" + JsonConvert.SerializeObject(mail) + "\n";
        }

        Console.WriteLine(JsonConvert.SerializeObject(context.Request.Query));

        return Results.Content(Utils.makeHTML("<b>PUT Success</b>" + result), "text/html");
    }
    catch (Exception ex)
    {
        Console.WriteLine("[ERROR] " + ex.Message + "\n" + ex.StackTrace);
        return Results.BadRequest();
    }
});
app.Run();