using System;
using System.Diagnostics;


namespace lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            //Student me = new Student();
            //Console.WriteLine(me.ToShortString());
            //me.AddExams(new Exam("Math", 5, new DateTime(2020, 07, 06)), new Exam("OOP", 5, new DateTime(2020, 07, 09)));
            //me.AddExams(new Exam("Physics", 4, new DateTime(2020, 07, 10)), new Exam("Russian", 4, new DateTime(2020, 07, 09)));
            //Console.WriteLine(me.ToString());

            //Console.WriteLine(me.ToShortString());

            Console.WriteLine("-----------#9 -----------");
            const int count1 = 1000000, count2 = 5, count3 = 200000;

            //Instantiate One-dimensional array
            Exam[] array1 = new Exam[count1];
            for (int i = 0; i < count1; i++)
                array1[i] = new Exam("Literature", 4, new DateTime(2020, 5, 5));

            //Instantiate two-dimensional rectangular array
            Exam[,] array2 = new Exam[count2, count3];
            for (int i = 0; i < count2; i++)
                for (int j = 0; j < count3; j++)
                    array2[i, j] = new Exam("Literature", 4, new DateTime(2020, 5, 5));

            //Instantiate two-dimensional stepped array
            Exam[][] array3 = new Exam[5][];

            array3[0] = new Exam[200000];
            array3[1] = new Exam[400000];
            array3[2] = new Exam[20000];
            array3[3] = new Exam[180000];
            array3[4] = new Exam[200000];

            for (int i = 0; i < 200000; i++)
                array3[0][i] = new Exam("Literature", 4, new DateTime(2020, 5, 5));

            for (int i = 0; i < 400000; i++)
                array3[1][i] = new Exam("Literature", 4, new DateTime(2020, 5, 5));

            for (int i = 0; i < 20000; i++)
                array3[2][i] = new Exam("Literature", 4, new DateTime(2020, 5, 5));

            for (int i = 0; i < 180000; i++)
                array3[3][i] = new Exam("Literature", 4, new DateTime(2020, 5, 5));

            for (int i = 0; i < 200000; i++)
                array3[4][i] = new Exam("Literature", 4, new DateTime(2020, 5, 5));

            Console.WriteLine("Time for one-dimensional array: ");
            var watch = Stopwatch.StartNew();

            for (int i = 0; i < count1; i++)
                array1[i].Mark = 4;

            watch.Stop();
            Console.WriteLine(watch.Elapsed);

            Console.WriteLine("Time for two-dimensional rectangular array");
            watch.Restart();

            for (int i = 0; i < count2; i++)
                for (int j = 0; j < count3; j++)
                    array2[i, j].Mark = 4;
            watch.Stop();

            Console.WriteLine(watch.Elapsed);

            Console.WriteLine("Time for two-dimensional stepped array");
            watch.Restart();

            for (int i = 0; i < 200000; i++)
                array3[0][i].Mark = 4;

            for (int i = 0; i < 400000; i++)
                array3[1][i].Mark = 4;

            for (int i = 0; i < 20000; i++)
                array3[2][i].Mark = 4;

            for (int i = 0; i < 180000; i++)
                array3[3][i].Mark = 4;

            for (int i = 0; i < 200000; i++)
                array3[4][i].Mark = 4;
            watch.Stop();

            Console.WriteLine(watch.Elapsed);
        }
    }
}
