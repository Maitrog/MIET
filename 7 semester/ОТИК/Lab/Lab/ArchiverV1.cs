﻿using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab
{
    internal class ArchiverV1
    {
        public static void Archive(string[] fileNames)
        {
            string currentDirectory = Directory.GetCurrentDirectory();
            FileStream archive = File.Create($"{currentDirectory}/archive1.lox");
            byte[] sign = { 0x0, 0x0, 0x0, 0xC, 0x0, 0xC, 0xE, 0xE };
            byte[] vers = { 0x1 };
            byte[] algorithm = { 0x1 };
            string[] codes = new string[256];
            byte[] data = Array.Empty<byte>();

            var stat = GetStatistic(fileNames);
            double[] probabilities = stat.Item3;
            byte[] alphabet = GetAlphabet();

            SortAlphabet(alphabet, probabilities);
            codes = GetCodes(alphabet, probabilities, codes);

            archive.Write(sign);

            archive.Write(vers);

            archive.Write(algorithm);

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

        private static byte[] DirectoryToBytes(string item)
        {
            byte[] data = Array.Empty<byte>();
            byte[] type = { 0x1 };
            data = data.Concat(type).ToArray();

            DirectoryInfo info = new DirectoryInfo(item);
            byte[] title = Encoding.UTF8.GetBytes(info.Name);
            data = data.Concat(BitConverter.GetBytes(title.Length)).ToArray();

            data = data.Concat(title).ToArray();

            var directories = info.GetDirectories();
            Array.ForEach(directories, d => data = data.Concat(DirectoryToBytes(d.FullName)).ToArray());

            var files = info.GetFiles();
            Array.ForEach(files, f => data = data.Concat(FileToBytes(f.FullName)).ToArray());

            var end = new byte[] { 0xFF, 0xFF };
            data = data.Concat(end).ToArray();

            return data;
        }

        private static byte[] FileToBytes(string item)
        {
            byte[] data = Array.Empty<byte>();
            byte[] type = { 0x0 };
            data = data.Concat(type).ToArray();

            FileInfo info = new FileInfo(item);
            byte[] title = Encoding.UTF8.GetBytes(info.Name);
            data = data.Concat(BitConverter.GetBytes(title.Length)).ToArray();

            data = data.Concat(title).ToArray();

            var bytes = File.ReadAllBytes(item);
            data = data.Concat(BitConverter.GetBytes(bytes.Length)).ToArray();

            data = data.Concat(bytes).ToArray();

            return data;
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

        private static byte[] CodeData(byte[] data, string[] codes)
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

        private static List<byte> DecodeData(in List<byte> data, string[] codes, int minLength)
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

        private static string[] GetCodes(byte[] alphabet, double[] probabilities, string[] codes)
        {
            if (alphabet.Length == 1)
            {
                return codes;
            }
            double left = probabilities.Take(1).Sum();
            double right = probabilities.Skip(1).Take(alphabet.Length - 1).Sum();

            byte[] leftSide = alphabet.Take(1).ToArray();
            byte[] rightSide = alphabet.Skip(1).Take(alphabet.Length - 1).ToArray();
            double[] leftProbabilities = probabilities.Take(1).ToArray();
            double[] rightProbabilities = probabilities.Skip(1).Take(alphabet.Length - 1).ToArray();
            string[] leftCode = codes.Take(1).ToArray();
            string[] rightCode = codes.Skip(1).Take(alphabet.Length - 1).ToArray();

            for (int j = 0; j < leftCode.Length; j++)
            {
                leftCode[j] = leftCode[j] + "0";
            }
            for (int j = 0; j < rightCode.Length; j++)
            {
                rightCode[j] = rightCode[j] + "1";
            }

            for (int i = 2; i < alphabet.Length; i++)
            {
                if (left >= right)
                {
                    if (i == 2)
                    {
                        break;
                    }
                    leftSide = alphabet.Take(i - 2).ToArray();
                    rightSide = alphabet.Skip(i - 2).Take(alphabet.Length - i + 2).ToArray();
                    leftProbabilities = probabilities.Take(i - 2).ToArray();
                    rightProbabilities = probabilities.Skip(i - 2).Take(alphabet.Length - i + 2).ToArray();
                    leftCode = codes.Take(i - 2).ToArray();
                    rightCode = codes.Skip(i - 2).Take(alphabet.Length - i + 2).ToArray();
                    for (int j = 0; j < leftCode.Length; j++)
                    {
                        leftCode[j] = leftCode[j] + "0";
                    }
                    for (int j = 0; j < rightCode.Length; j++)
                    {
                        rightCode[j] = rightCode[j] + "1";
                    }
                    break;
                }
                left = probabilities.Take(i).Sum();
                right = probabilities.Skip(i).Take(alphabet.Length - i).Sum();
            }

            leftCode = GetCodes(leftSide, leftProbabilities, leftCode);
            rightCode = GetCodes(rightSide, rightProbabilities, rightCode);
            codes = leftCode.Concat(rightCode).ToArray();
            return codes;
        }

        private static void SortAlphabet(byte[] alphabet, double[] probabilities)
        {
            for (int i = 0; i < alphabet.Length; i++)
            {
                for (int j = i; j < alphabet.Length; j++)
                {
                    if (probabilities[j] > probabilities[i])
                    {
                        double tmp = probabilities[i];
                        probabilities[i] = probabilities[j];
                        probabilities[j] = tmp;

                        byte tmp2 = alphabet[i];
                        alphabet[i] = alphabet[j];
                        alphabet[j] = tmp2;
                    }
                }
            }
        }

        private static void SortCode(string[] code, byte[] alphabet)
        {
            for (int i = 0; i < code.Length; i++)
            {
                for (int j = i; j < code.Length; j++)
                {
                    if (alphabet[j] < alphabet[i])
                    {
                        byte tmp = alphabet[i];
                        alphabet[i] = alphabet[j];
                        alphabet[j] = tmp;

                        string tmp2 = code[i];
                        code[i] = code[j];
                        code[j] = tmp2;
                    }
                }
            }
        }

        private static byte[] GetAlphabet()
        {
            byte[] alphabet = new byte[256];
            for (int i = 0; i < alphabet.Length; i++)
            {
                alphabet[i] = (byte)i;
            }
            return alphabet;
        }

        private static (long, long[], double[], double[], double) GetStatistic(string[] fileNames)
        {
            long length = 0;
            long[] frequencies = new long[256];
            double[] probabilities = new double[256];
            double[] I = new double[256];
            double sumI = 0;

            foreach (var item in fileNames)
            {
                if (File.Exists(item))
                {
                    FileInfo fi = new FileInfo(item);
                    length += fi.Length;
                }
                if (Directory.Exists(item))
                {
                    DirectoryInfo di = new DirectoryInfo(item);
                    length += DirSize(di);
                }
            }

            foreach (var item in fileNames)
            {
                if (File.Exists(item))
                {
                    var file = File.ReadAllBytes(item);
                    foreach (var b in file)
                    {
                        frequencies[b]++;
                    }
                }
                if (Directory.Exists(item))
                {
                    DirectoryInfo di = new DirectoryInfo(item);
                    DirFrequency(frequencies, di);
                }
            }

            for (int i = 0; i < frequencies.Length; i++)
            {
                long frequency = frequencies[i];
                probabilities[i] = (double)frequency / length;
            }

            for (int i = 0; i < probabilities.Length; i++)
            {
                double probability = probabilities[i];
                I[i] = -Math.Log2(probability);
            }

            for (int i = 0; i < I.Length; i++)
            {
                // хз как правильно найти суммарное количество информации
                //sumI += probabilities[i] * I[i];
                sumI += probabilities[i];
            }
            return (length, frequencies, probabilities, I, sumI);
        }

        private static void DirFrequency(long[] frequency, DirectoryInfo di)
        {
            var files = di.GetFiles();
            foreach (var f in files)
            {
                var file = File.ReadAllBytes(f.FullName);
                foreach (var b in file)
                {
                    frequency[b]++;
                }
            }

            var directories = di.GetDirectories();
            Array.ForEach(directories, d => DirFrequency(frequency, d));
        }

        private static long DirSize(DirectoryInfo di)
        {
            long length = 0;

            var files = di.GetFiles();
            Array.ForEach(files, f => length += f.Length);

            var directories = di.GetDirectories();
            Array.ForEach(directories, d => length += DirSize(d));

            return length;
        }

        static byte[] GetBytes(string str)
        {
            int numOfBytes = str.Length / 8;
            byte[] bytes = new byte[numOfBytes];
            for (int i = 0; i < numOfBytes; ++i)
            {
                bytes[i] = Convert.ToByte(str.Substring(8 * i, 8), 2);
            }

            return bytes;
        }
    }
}
