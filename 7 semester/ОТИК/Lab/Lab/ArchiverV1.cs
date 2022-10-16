using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab
{
    internal class ArchiverV1 : Archiver
    {
        public static void Archive(string[] fileNames, byte algorithm = 0x1)
        {
            string currentDirectory = Directory.GetCurrentDirectory();
            FileStream archive = File.Create($"{currentDirectory}/archive1.lox");
            byte[] sign = { 0x0, 0x0, 0x0, 0xC, 0x0, 0xC, 0xE, 0xE };
            byte[] vers = { 0x1 };
            string[] codes = new string[256];
            byte[] data = Array.Empty<byte>();

            var stat = GetStatistic(fileNames);
            double[] probabilities = stat.Item3;
            byte[] alphabet = GetAlphabet();

            SortAlphabet(alphabet, probabilities);
            codes = GetCodes(alphabet, probabilities, codes);

            archive.Write(sign);

            archive.Write(vers);

            archive.Write(new byte[1] { algorithm });

            archive.Write(alphabet);

            byte[] probabilitiesBytes = new byte[probabilities.Length * sizeof(double)];
            Buffer.BlockCopy(probabilities, 0, probabilitiesBytes, 0, probabilitiesBytes.Length);
            archive.Write(probabilitiesBytes);


            SortCode(codes, alphabet);

            foreach (var item in fileNames)
            {
                if (Directory.Exists(item))
                {
                    data = data.Concat(DirectoryToBytes(item)).ToArray();
                }
                else
                {
                    data = data.Concat(FileToBytes(item)).ToArray();
                }
            }

            var end = new byte[] { 0x0, 0x0 };

            data = CodeData(data, codes);
            archive.Write(data);

            archive.Write(end);
            archive.Close();
        }

        public static void Dearchive(string currentDirectory, int readed, List<byte> archive)
        {
            var algorithm = archive.Skip(readed).Take(1).ToArray()[0];
            readed++;

            var alphabet = archive.Skip(readed).Take(256).ToArray();
            readed += 256;

            double[] probabilities = new double[256];
            var probabilitiesBytes = archive.Skip(readed).Take(2048).ToArray();
            readed += 2048;

            Buffer.BlockCopy(probabilitiesBytes, 0, probabilities, 0, probabilitiesBytes.Length);

            string[] codes = new string[256];
            codes = GetCodes(alphabet, probabilities, codes);
            SortCode(codes, alphabet);

            List<byte> data = archive.Skip(readed).Take(archive.Count - readed - 2).ToList();
            readed += archive.Count - readed - 2;

            int minLength = 100;
            Array.ForEach(codes, code => minLength = code.Length < minLength ? code.Length : minLength);
            data = DecodeData(data, codes, minLength);
            data = data.Concat(archive.Skip(readed).Take(2)).ToList();

            readed = 0;

            while (true)
            {
                var type = data.Skip(readed).Take(1).ToArray()[0];
                readed++;

                if (type == 0x1)
                {
                    readed = ReadDirectory(currentDirectory, readed, data);
                }
                else
                {
                    readed = ReadFile(currentDirectory, readed, data);
                }

                var end = data.Skip(readed).Take(2).ToArray();
                if (end[0] == 0x0 && end[1] == 0x0)
                {
                    break;
                }
            }
        }

        public static byte[] CodeData(byte[] data, string[] codes)
        {
            List<byte> newData = new List<byte>();
            StringBuilder sb = new StringBuilder();
            var bytes = new byte[0];

            foreach (var item in data)
            {
                sb.Append(codes[item]);
                while(sb.Length > 8)
                {
                    bytes = GetBytes(sb.ToString(0, 8));
                    Array.ForEach(bytes, b => newData.Add(b));
                    sb.Remove(0, 8);
                }
            }

            int zeroCount = 8 - sb.Length % 8;
            sb.Append(new string('0', zeroCount));
            bytes = GetBytes(sb.ToString(0, 8));
            Array.ForEach(bytes, b => newData.Add(b));
            sb.Remove(0, 8);

            return newData.ToArray();
        }

        public static List<byte> DecodeData(in List<byte> data, string[] codes, int minLength)
        {
            List<byte> newData = new List<byte>();
            StringBuilder sb = new StringBuilder(24);

            var watch = new System.Diagnostics.Stopwatch();
            watch.Start();
            int j = 0;
            foreach (var item in data)
            {
                j++;
                sb.Append(Convert.ToString(item, 2).PadLeft(8, '0'));

                if (sb.Length >= minLength)
                {
                    if(j % 10000 == 0)
                    {
                        watch.Stop();
                        Console.WriteLine($"Execution Time: {watch.ElapsedMilliseconds} ms");

                        watch.Restart();
                    }

                    StringBuilder tmp = new StringBuilder(24);
                    tmp.Append(sb.ToString(0, minLength));
                    for (int i = minLength; i < sb.Length; i++)
                    {
                        int index = Array.IndexOf(codes, tmp.ToString());
                        if (index != -1)
                        {
                            newData.Add(Convert.ToByte(index));
                            sb.Remove(0, tmp.Length);
                            tmp.Clear();
                            var elementCount = sb.Length >= minLength ? minLength : sb.Length;
                            i = elementCount - 1;
                            tmp.Append(sb.ToString(0, elementCount));
                        }
                        else
                        {
                            tmp.Append(sb[i]);
                        }
                    }
                }
            }
            watch.Stop();
            Console.WriteLine($"Execution Time: {watch.ElapsedMilliseconds} ms");

            return newData;
        }
    }
}
