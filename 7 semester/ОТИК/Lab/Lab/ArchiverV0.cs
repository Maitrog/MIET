using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab
{
    internal class ArchiverV0
    {
        public static void Archieve(string[] fileNames)
        {
            string currentDirectory = Directory.GetCurrentDirectory();
            FileStream archive = File.Create($"{currentDirectory}/archive0.lox");
            byte[] sign = { 0x0, 0x0, 0x0, 0xC, 0x0, 0xC, 0xE, 0xE };
            byte[] vers = { 0x0 };

            archive.Write(sign);

            archive.Write(vers);

            foreach (var item in fileNames)
            {
                if (Directory.Exists(item))
                {
                    WriteDirectory(archive, item);
                }
                else
                {
                    WriteFile(archive, item);
                }
            }

            var end = new byte[] { 0x0, 0x0 };
            archive.Write(end);

            archive.Close();
        }

        public static void Dearchive(string currentDirectory, int readed, List<byte> archive)
        {
            while (true)
            {
                var type = archive.Skip(readed).Take(1).ToArray()[0];
                readed++;

                if (type == 0x1)
                {
                    readed = ReadDirectory(currentDirectory, readed, archive);
                }
                else
                {
                    readed = ReadFile(currentDirectory, readed, archive);
                }

                var end = archive.Skip(readed).Take(2).ToArray();
                if (end[0] == 0x0 && end[1] == 0x0)
                {
                    break;
                }
            }
        }

        private static void WriteDirectory(FileStream archive, string item)
        {
            byte[] type = { 0x1 };
            archive.Write(type);

            DirectoryInfo info = new DirectoryInfo(item);
            byte[] title = Encoding.UTF8.GetBytes(info.Name);
            archive.Write(BitConverter.GetBytes(title.Length));

            archive.Write(title);

            var directories = info.GetDirectories();
            Array.ForEach(directories, d => WriteDirectory(archive, d.FullName));

            var files = info.GetFiles();
            Array.ForEach(files, f => WriteFile(archive, f.FullName));

            var end = new byte[] { 0xFF, 0xFF };
            archive.Write(end);
        }

        private static void WriteFile(FileStream archive, string item)
        {
            byte[] type = { 0x0 };
            archive.Write(type);

            FileInfo info = new FileInfo(item);
            byte[] title = Encoding.UTF8.GetBytes(info.Name);
            archive.Write(BitConverter.GetBytes(title.Length));

            archive.Write(title);

            var bytes = File.ReadAllBytes(item);
            archive.Write(BitConverter.GetBytes(bytes.Length));

            archive.Write(bytes);
        }

        private static int ReadDirectory(string currentDirectory, int readed, List<byte> archive)
        {
            int titleLength = BitConverter.ToInt32(archive.Skip(readed).Take(4).ToArray());
            readed += 4;

            string title = Encoding.UTF8.GetString(archive.Skip(readed).Take(titleLength).ToArray());
            readed += titleLength;

            currentDirectory = $"{currentDirectory}/{title}";
            Directory.CreateDirectory(currentDirectory);

            while (true)
            {
                var type = archive.Skip(readed).Take(1).ToArray()[0];
                readed++;

                if (type == 0x1)
                {
                    readed = ReadDirectory(currentDirectory, readed, archive);
                }
                else
                {
                    readed = ReadFile(currentDirectory, readed, archive);
                }

                var end = archive.Skip(readed).Take(2).ToArray();
                if (end[0] == 0xFF && end[1] == 0xFF)
                {
                    readed += 2;
                    break;
                }
            }

            return readed;
        }

        private static int ReadFile(string currentDirectory, int readed, List<byte> archive)
        {
            int titleLength = BitConverter.ToInt32(archive.Skip(readed).Take(4).ToArray());
            readed += 4;

            string title = Encoding.UTF8.GetString(archive.Skip(readed).Take(titleLength).ToArray());
            readed += titleLength;

            FileStream file = File.Create($"{currentDirectory}/{title}");

            int fileLength = BitConverter.ToInt32(archive.Skip(readed).Take(4).ToArray());
            readed += 4;

            file.Write(archive.Skip(readed).Take(fileLength).ToArray());
            readed += fileLength;

            file.Close();
            return readed;
        }
    }
}
