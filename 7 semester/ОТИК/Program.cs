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
            foreach (var item in args)
            {
                Console.WriteLine(item);
            }

            if (args.Length > 0)
            {
                if (args[0] == "-a")
                {
                    ArchieveV0(args.Skip(1).Take(args.Length - 1).ToArray());
                }
                else if (args[0] == "-d")
                {
                    DearchiveV0(args.Skip(1).Take(1).ToArray()[0]);
                }
            }
        }

        static void ArchieveV0(string[] fileNames)
        {
            string currentDirectory = Directory.GetCurrentDirectory();
            FileStream archive = File.Create($"{currentDirectory}/archive.lox");
            int archiveLength = 0;
            byte[] sign = { 0x0, 0x0, 0x0, 0xC, 0x0, 0xC, 0xE, 0xE };
            byte[] vers = { 0x0 };
            long length = 0;

            foreach (var item in fileNames)
            {
                FileInfo info = new FileInfo(item);
                length += info.Length;
            }

            archive.Write(sign);
            archiveLength += 8;

            archive.Write(vers);
            archiveLength += 1;

            archive.Write(BitConverter.GetBytes(length));
            archiveLength += 8;

            foreach (var item in fileNames)
            {
                FileInfo info = new FileInfo(item);
                byte[] title = Encoding.ASCII.GetBytes(info.Name);
                archive.Write(BitConverter.GetBytes(title.Length));
                archiveLength += 4;

                archive.Write(title);
                archiveLength += title.Length;

                var bytes = File.ReadAllBytes(item);
                archive.Write(BitConverter.GetBytes(bytes.Length));
                archiveLength += 4;

                archive.Write(bytes);
                archiveLength += bytes.Length;
            }

            var end = new byte[] { 0x0, 0x0 };
            archive.Write(end);

            archive.Close();
        }

        static void DearchiveV0(string fileName)
        {
            string currentDirectory = Directory.GetCurrentDirectory();
            byte[] sign = { 0x0, 0x0, 0x0, 0xC, 0x0, 0xC, 0xE, 0xE };
            byte[] vers = { 0x0 };
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

            readed += 9;
            while (true)
            {
                int titleLength = BitConverter.ToInt32(archive.Skip(readed).Take(4).ToArray());
                readed += 4;

                string title = Encoding.ASCII.GetString(archive.Skip(readed).Take(titleLength).ToArray());
                readed += titleLength;

                FileStream file = File.Create($"{currentDirectory}/{title}");

                int fileLength = BitConverter.ToInt32(archive.Skip(readed).Take(4).ToArray());
                readed += 4;

                file.Write(archive.Skip(readed).Take(fileLength).ToArray());
                readed += fileLength;

                file.Close();

                var end = archive.Skip(readed).Take(2).ToArray();
                if (end[0] == 0x0 && end[1] == 0x0)
                {
                    break;
                }
            }
        }
    }
}
