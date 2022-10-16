using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab
{
    internal class ArchiverV5 : Archiver
    {
        private static int countOfBits = 48;
        private static int maxDecodeBytes = 13;
        public static void Archive(string[] fileNames, byte algorithm = 0x8)
        {
            string currentDirectory = Directory.GetCurrentDirectory();
            FileStream archive = File.Create($"{currentDirectory}/archive5.lox");
            byte[] sign = { 0x0, 0x0, 0x0, 0xC, 0x0, 0xC, 0xE, 0xE };
            byte[] vers = { 0x5 };
            string[] codes = new string[256];
            byte[] data = Array.Empty<byte>();

            archive.Write(sign);

            archive.Write(vers);

            archive.Write(new byte[1] { algorithm });

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

            var stat = GetStatistic(data);
            double[] probabilities = stat.Item3;
            byte[] alphabet = GetAlphabet();
            SortAlphabet(alphabet, probabilities);

            archive.Write(alphabet);

            var intervals = GetIntervals(probabilities, 0, 1);

            byte[] probabilitiesBytes = new byte[probabilities.Length * sizeof(double)];
            Buffer.BlockCopy(probabilities, 0, probabilitiesBytes, 0, probabilitiesBytes.Length);
            archive.Write(probabilitiesBytes);

            if (algorithm == 0x9)
            {
                codes = GetCodes(alphabet, probabilities, codes);

                SortCode(codes, alphabet);
            }

            archive.Write(new byte[1] { alphabet.Last() });

            data = ArithmeticArchive(data, probabilities, alphabet, intervals).ToArray();

            if (algorithm == 0x9)
            {
                data = ArchiverV1.CodeData(data, codes);
            }

            data = ArchiverV3.ArchiveLZ77(data, alphabet.Last());

            var end = new byte[] { 0x0, 0x0 };

            archive.Write(data);

            archive.Write(end);
            archive.Close();
        }

        public static void Dearchive(string currentDirectory, int readed, List<byte> archive)
        {

            var algorithm = archive.Skip(readed).First();
            readed++;

            var alphabet = archive.Skip(readed).Take(256).ToArray();
            readed += 256;

            double[] probabilities = new double[256];
            var probabilitiesBytes = archive.Skip(readed).Take(2048).ToArray();
            readed += 2048;

            Buffer.BlockCopy(probabilitiesBytes, 0, probabilities, 0, probabilitiesBytes.Length);

            var intervals = GetIntervals(probabilities, 0, 1);

            string[] codes = new string[256];
            if (algorithm == 0x9)
            {
                codes = GetCodes(alphabet, probabilities, codes);
                SortCode(codes, alphabet.ToArray());
            }

            var prefix = archive.Skip(readed).First();
            readed++;

            List<byte> data = archive.Skip(readed).Take(archive.Count - readed - 2).ToList();
            readed += archive.Count - readed - 2;

            if (algorithm == 0x9)
            {
                int minLength = 100;
                Array.ForEach(codes, code => minLength = code.Length < minLength ? code.Length : minLength);
                data = ArchiverV1.DecodeData(data, codes, minLength);
            }

            data = ArchiverV3.DearchiveLZ77(data, prefix);

            data = ArithmeticDearchive(data, intervals, probabilities, alphabet);

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
                else if (type == 0x0)
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

        private static List<byte> ArithmeticDearchive(List<byte> data, double[] intervals, double[] probabilities, byte[] alphabet)
        {
            FileStream logFS = File.Open(@"C:\Users\Mihay\Documents\MIET\7 semester\ОТИК\Lab\Lab\bin\Debug\net6.0\dearchiveLog.txt", FileMode.OpenOrCreate);
            List<byte> newData = new List<byte>((int)(data.Count * 1.2));

            for (int i = 0; i < data.Count; i += 6)
            {
                var block = data.Skip(i).Take(6).ToArray();
                var binStr = BytesToBinaryString(block);
                var first = BinaryStringToDouble(binStr, maxDecodeBytes + 1);

                int count = 0;
                double[] newIntervals = intervals.ToArray();
                while (count != maxDecodeBytes && newIntervals[^1] - newIntervals[0] > 0.00000000000001000)
                {
                    int index = FindNewIntervals(newIntervals, first);
                    newIntervals = GetIntervals(probabilities, newIntervals[index], newIntervals[index + 1]);
                    if (newIntervals[^1] - newIntervals[0] >= 0.00000000000000900)
                    {
                        logFS.Write(Encoding.UTF8.GetBytes(string.Concat(index.ToString(), "\n")));
                        newData.Add(alphabet[index]);
                        count++;
                    }
                }
                logFS.Write(Encoding.UTF8.GetBytes("---------------------------\n"));
            }
            return newData;
        }

        private static int FindNewIntervals(double[] intervals, double element)
        {
            double epsilon = 1e-16;
            if (element < intervals[0])
            {
                return 0;
            }
            if (element > intervals[^1])
            {
                return 255;
            }
            for (int i = 0; i < intervals.Length - 1; i++)
            {
                if (intervals[i] <= element
                    && (intervals[i + 1] + epsilon >= element || (i + 1 == intervals.Length - 1 && intervals[i + 1] == element)))
                {
                    return i;
                }
            }
            return -1;
        }

        private static List<byte> ArithmeticArchive(byte[] data, double[] probabilities, byte[] alphabet, double[] intervals)
        {
            FileStream logFS = File.Open(@"C:\Users\Mihay\Documents\MIET\7 semester\ОТИК\Lab\Lab\bin\Debug\net6.0\archiveLog.txt", FileMode.OpenOrCreate);
            double[] newIntervals = intervals.ToArray();
            List<byte> newData = new List<byte>(data.Length);
            int count = 0;
            for (int i = 0; i < data.Length; i++)
            {
                int startIndex = Array.IndexOf(alphabet, data[i]);
                if (count == maxDecodeBytes || newIntervals[startIndex + 1] - newIntervals[startIndex] <= 0.00000000000001000)
                {
                    newData.AddRange(GetBytes(DoubleToBinaryString(newIntervals[^1])));

                    newIntervals = intervals.ToArray();
                    i--;
                    count = 0;
                    logFS.Write(Encoding.UTF8.GetBytes("---------------------------\n"));
                }
                else
                {
                    logFS.Write(Encoding.UTF8.GetBytes(string.Concat(startIndex.ToString(), "\n")));
                    newIntervals = GetIntervals(probabilities, newIntervals[startIndex], newIntervals[startIndex + 1]);
                    count++;
                }
            }
            newData.AddRange(GetBytes(DoubleToBinaryString(newIntervals[^1])));

            return newData;
        }

        private static double[] GetIntervals(double[] probabilities, double startPosition, double lastPosition)
        {
            decimal[] intervals = new decimal[probabilities.Length + 1];
            intervals[0] = (decimal)startPosition;
            for (int i = 0; i < probabilities.Length; i++)
            {
                intervals[i + 1] = intervals[i] + (decimal)(probabilities[i]) * ((decimal)lastPosition - (decimal)startPosition);
            }

            var result = intervals.Select(x => Round(x, countOfBits / 8)).ToArray();

            result[^1] = lastPosition;

            return result;
        }

        private static string DoubleToBinaryString(double val)
        {
            long v = (long)(val * 100000000000000);
            string binary = Convert.ToString(v, 2);
            return binary.PadLeft(countOfBits, '0');
        }

        private static double BinaryStringToDouble(string str, int? digits = null)
        {
            long v = Convert.ToInt64(str, 2);
            double countOfNumbers = Math.Floor(Math.Log10(v) + 1);
            if (digits > countOfNumbers)
            {
                countOfNumbers = (double)digits;
            }

            double result = v / Math.Pow(10, countOfNumbers);
            return result;
        }

        private static string BytesToBinaryString(byte[] data)
        {
            StringBuilder sb = new StringBuilder();
            foreach (var item in data)
            {
                sb.Append(Convert.ToString(item, 2).PadLeft(8, '0'));
            }
            return sb.ToString();
        }

        private static double Round(decimal value, int digits)
        {
            var v = (value * Convert.ToDecimal(Math.Pow(10, 17)));
            v = Math.Round(v);
            double result = (long)(v) / Math.Pow(10, 17);
            return result;
        }
    }
}
