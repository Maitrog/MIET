using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_6.Observer
{
    internal class Department : IObserver
    {
        public void Update(ISubject subject)
        {
            if (subject is Deanery deanery)
            {
                Console.WriteLine($"Кафедра получила список из {deanery.TeachersWhoDidNotReport.Count} преподавателей, не сдавших отчёт.");
                if (deanery.TeachersWhoDidNotReport.Count > 0)
                {
                    Console.WriteLine("Не сдали отчет:");
                    foreach (var teacher in deanery.TeachersWhoDidNotReport)
                        Console.WriteLine(teacher.Name);
                }
                Console.WriteLine("------------------------------------------");
            }
            else
            {
                throw new Exception("Всё плохо");
            }
        }
    }
}
