using Newtonsoft.Json;
using System.Text;

namespace Lab6.Models
{
    public static class Utils
    {
        public static async Task<int> addNewMailToDBAsync(IWebHostEnvironment appEnvironment, MailData mail)
        {
            try
            {
                Mail[] mailList = JsonConvert.DeserializeObject<Mail[]>(getAllData());
                var increment = mailList != null ? mailList.Length + 1 : 1;
                mail.Id = "mail_" + increment;

                if (!Directory.Exists("/UserFiles"))
                {
                    Directory.CreateDirectory(Directory.GetCurrentDirectory() + "/UserFiles");
                }
                string path = "";
                if (mail.File != null)
                {
                    path = Directory.GetCurrentDirectory() + "/UserFiles/" + mail.File.FileName;
                    using (var fs = new FileStream(path, FileMode.Create))
                    {
                        await mail.File.CopyToAsync(fs);
                    }
                }

                Array.Resize(ref mailList, increment);
                Mail newMail = new()
                {
                    Id = mail.Id,
                    Datetime = mail.Datetime,
                    Subject = mail.Subject,
                    From = mail.From,
                    Message = mail.Message,
                    Path = path
                };
                mailList[increment - 1] = newMail;
                saveAllData(JsonConvert.SerializeObject(mailList));

                return increment;
            }
            catch (Exception e)
            {
                Console.WriteLine("[ERROR] " + e.Message + "\n" + e.StackTrace);
                return -1;
            }
        }

        public static string makeHTML(string data)
        {
            string result = "<html><head><meta charset=\"utf-8\"></head><body>" + data + "</body></html>";
            return result;
        }

        public static string makeFilter(Microsoft.Extensions.Primitives.StringValues stringValues)
        {
            string result = "makeFilter";
            Mail[] data = JsonConvert.DeserializeObject<Mail[]>(getAllData());

            //Поиск по названию
            if (stringValues.Count != 0)
            {
                foreach (Mail mail in data)
                {
                    Console.WriteLine(mail.Subject + " " + stringValues.ToString());
                    var temp = mail.Subject;
                    if (stringValues.Contains(temp))
                    {
                        result += JsonConvert.SerializeObject(mail);
                    }
                }
            }
            return result;
        }

        public static string getAllData()
        {
            string filePath = Directory.GetCurrentDirectory() + "/maillist.json";
            if (!File.Exists(filePath))
            {
                File.Create(filePath);
            }
            string result;
            try
            {
                result = File.ReadAllText(filePath, Encoding.UTF8);
                return result;
            }
            catch (Exception e)
            {
                sendErr(e, "Error BD access", 0);
                return "";
            }
        }

        public static bool saveAllData(string data)
        {
            string filePath = Directory.GetCurrentDirectory() + "/maillist.json";
            if (!File.Exists(filePath))
            {
                File.Create(filePath);
            }

            File.WriteAllText(filePath, data);
            return true;
        }

        public static void sendErr(Exception e, string msg, int code)
        {
            throw new Exception("[ERROR]: " + code + " " + e.Message + "\n" + e.StackTrace);
        }
    }
}
