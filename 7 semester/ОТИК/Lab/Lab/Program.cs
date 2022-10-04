using Lab;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace ArchieveTest
{
    class Program
    {
        static void Main(string[] args)
        {
            ArchiverV3.Archive(new string[] { @"C:\Users\Mihay\Documents\Фото" });
            Dearchive(@"C:\Users\Mihay\Documents\MIET\7 semester\ОТИК\Lab\Lab\bin\Debug\net6.0\archive3.lox");
            //int version = 1;
            //if(args.Length == 4)
            //{
            //    if(args[2] == "-v")
            //    {
            //        version = int.Parse(args[3]);
            //    }
            //}
            //if (args.Length > 0)
            //{
            //    if (args[0] == "-a")
            //    {
            //        Archive(args.Skip(1).Take(args.Length - 1).ToArray(), version);
            //    }
            //    else if (args[0] == "-d")
            //    {
            //        Dearchive(args.Skip(1).Take(1).ToArray()[0]);
            //    }
            //}
        }

        static void Archive(string[] fileNames, int version = 0, int archiveStyle = 1)
        {
            if (version == 0)
            {
                ArchiverV0.Archieve(fileNames);
            }
            else if (version == 1)
            {
                ArchiverV1.Archive(fileNames);
            }
        }

        static void Dearchive(string fileName)
        {
            string currentDirectory = Directory.GetCurrentDirectory();
            byte[] sign = { 0x0, 0x0, 0x0, 0xC, 0x0, 0xC, 0xE, 0xE };
            int readed = 0;

            List<byte> archive = new List<byte>(File.ReadAllBytes(fileName));
            List<byte> fileSign = archive.Take(8).ToList();
            readed += 8;

            for (int i = 0; i < 8; i++)
            {
                if (fileSign[i] != sign[i])
                {
                    Console.WriteLine("Error");
                    break;
                }
            }

            byte vers = archive.Skip(readed).Take(1).ToArray()[0];
            readed++;

            if (vers == 0)
            {
                ArchiverV0.Dearchive(currentDirectory, readed, archive);
            }
            if (vers == 1)
            {
                ArchiverV1.Dearchive(currentDirectory, readed, archive);
            }
            if(vers == 3)
            {
                ArchiverV3.Dearchive(currentDirectory, readed, archive);
            }
        }
    }
}
