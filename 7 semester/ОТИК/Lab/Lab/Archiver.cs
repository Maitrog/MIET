using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab
{
    internal abstract class Archiver
    {
        public static byte[] DirectoryToBytes(string item)
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

        public static byte[] FileToBytes(string item)
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

        public static int ReadDirectory(string currentDirectory, int readed, List<byte> archive)
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

        public static int ReadFile(string currentDirectory, int readed, List<byte> archive)
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

        public static string[] GetCodes(byte[] alphabet, double[] probabilities, string[] codes)
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

        public static void SortAlphabet(byte[] alphabet, double[] probabilities)
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

        public static void SortCode(string[] code, byte[] alphabet)
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

        public static (long, long[], double[], double[], double) GetStatistic(string[] fileNames)
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

        public static (long, long[], double[], double[], double) GetStatistic(byte[] data)
        {
            long length = data.Length;
            long[] frequencies = new long[256];
            double[] probabilities = new double[256];
            double[] I = new double[256];
            double sumI = 0;

            foreach (var b in data)
            {
                frequencies[b]++;
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

        public static byte[] GetAlphabet()
        {
            byte[] alphabet = new byte[256];
            for (int i = 0; i < alphabet.Length; i++)
            {
                alphabet[i] = (byte)i;
            }
            return alphabet;
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

        protected static byte[] GetBytes(string str)
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
