using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab
{
    internal class ArchiverV3
    {
        public static void Archive(string[] fileNames, byte algorithm = 0x4)
        {
            string currentDirectory = Directory.GetCurrentDirectory();
            FileStream archive = File.Create($"{currentDirectory}/archive3.lox");
            byte[] sign = { 0x0, 0x0, 0x0, 0xC, 0x0, 0xC, 0xE, 0xE };
            byte[] vers = { 0x3 };
            string[] codes = new string[256];
            byte[] data = Array.Empty<byte>();

            archive.Write(sign);

            archive.Write(vers);

            archive.Write(new byte[1] { algorithm });

            var stat = ArchiverV1.GetStatistic(fileNames);
            double[] probabilities = stat.Item3;
            byte[] alphabet = ArchiverV1.GetAlphabet();
            ArchiverV1.SortAlphabet(alphabet, probabilities);

            if (algorithm == 0x5)
            {
                codes = ArchiverV1.GetCodes(alphabet, probabilities, codes);

                archive.Write(alphabet);

                byte[] probabilitiesBytes = new byte[probabilities.Length * sizeof(double)];
                Buffer.BlockCopy(probabilities, 0, probabilitiesBytes, 0, probabilitiesBytes.Length);
                archive.Write(probabilitiesBytes);

                ArchiverV1.SortCode(codes, alphabet);

            }

            archive.Write(new byte[1] { alphabet.Last() });

            foreach (var item in fileNames)
            {
                if (Directory.Exists(item))
                {
                    data = data.Concat(ArchiverV1.DirectoryToBytes(item)).ToArray();
                }
                else
                {
                    data = data.Concat(ArchiverV1.FileToBytes(item)).ToArray();
                }
            }

            if (algorithm == 0x5)
            {
                data = ArchiverV1.CodeData(data, codes);
            }

            data = ArchiveLZ77(data, alphabet.Last());

            var end = new byte[] { 0x0, 0x0 };

            archive.Write(data);

            archive.Write(end);
            archive.Close();
        }

        public static void Dearchive(string currentDirectory, int readed, List<byte> archive)
        {

            var algorithm = archive.Skip(readed).First();
            readed++;

            string[] codes = new string[256];
            if (algorithm == 0x5)
            {

                var alphabet = archive.Skip(readed).Take(256).ToArray();
                readed += 256;

                double[] probabilities = new double[256];
                var probabilitiesBytes = archive.Skip(readed).Take(2048).ToArray();
                readed += 2048;

                Buffer.BlockCopy(probabilitiesBytes, 0, probabilities, 0, probabilitiesBytes.Length);

                codes = ArchiverV1.GetCodes(alphabet, probabilities, codes);
                ArchiverV1.SortCode(codes, alphabet);
            }

            var prefix = archive.Skip(readed).First();
            readed++;

            List<byte> data = archive.Skip(readed).Take(archive.Count - readed - 2).ToList();
            readed += archive.Count - readed - 2;

            if (algorithm == 0x5)
            {
                int minLength = 100;
                Array.ForEach(codes, code => minLength = code.Length < minLength ? code.Length : minLength);
                data = ArchiverV1.DecodeData(data, codes, minLength);
            }

            data = DearchiveLZ77(data, prefix);
            data = data.Concat(archive.Skip(readed).Take(2)).ToList();

            readed = 0;

            while (true)
            {
                var type = data.Skip(readed).Take(1).ToArray()[0];
                readed++;

                if (type == 0x1)
                {
                    readed = ArchiverV1.ReadDirectory(currentDirectory, readed, data);
                }
                else
                {
                    readed = ArchiverV1.ReadFile(currentDirectory, readed, data);
                }

                var end = data.Skip(readed).Take(2).ToArray();
                if (end[0] == 0x0 && end[1] == 0x0)
                {
                    break;
                }
            }
        }

        private static byte[] ArchiveLZ77(byte[] data, byte prefix)
        {
            StringBuilder str = new StringBuilder((int)(data.Length * 2.5));
            for (int i = 0; i < data.Length; i += 1023)
            {
                List<byte> subData = data.Skip(i).Take(1023).ToList();
                subData.Add(0xFF);
                Crochemore crochemore = new Crochemore(subData.ToArray(), 4);
                string newStr = ReplaceRepeat(crochemore, prefix);
                if (prefix == 0xFF)
                {
                    newStr = newStr.Remove(newStr.Length - 6, 6);
                }
                else
                {
                    newStr = newStr.Remove(newStr.Length - 2, 2);
                }
                str.Append(newStr);
            }

            return ConvertStringToBytes(str.ToString());
        }

        private static List<byte> DearchiveLZ77(List<byte> data, byte prefix)
        {
            string stringPrefix = prefix.ToString("X2");
            StringBuilder inputData = ConvertBytesToString(data);
            StringBuilder outputStr = new StringBuilder((int)(inputData.Length * 1.5));
            for (int i = 0; i < inputData.Length; i += 2)
            {
                string curentByte = inputData.ToString(i, 2);
                if (curentByte == stringPrefix)
                {
                    string code = inputData.ToString(i + 2, 4);
                    int numberCode = Convert.ToInt32(code, 16);
                    int L = (numberCode & 0b1111110000000000) >> 10;
                    int S = numberCode & 0b0000001111111111;
                    if (S == 0 && L == 0)
                    {
                        outputStr.Append(curentByte);
                    }
                    else
                    {
                        string sequence = outputStr.ToString(outputStr.Length - S, L);
                        outputStr.Append(sequence);
                    }
                    i += 4;
                }
                else
                {
                    outputStr.Append(curentByte);
                }
            }
            return ConvertStringToBytes(outputStr.ToString()).ToList();
        }

        private static string ReplaceRepeat(Crochemore crochemore, byte prefix)
        {
            StringBuilder str = new StringBuilder(crochemore.ByteString.Length);
            var substrings = crochemore.Substrings;
            substrings.Reverse();
            RemoveRepeatInex(substrings);
            string stringPrefix = prefix.ToString("X2");

            for (int i = 0; i < crochemore.ByteString.Length - 1; i += 2)
            {
                bool isSequence = false;
                string curentByte = crochemore.ByteString[i..(i + 2)];
                if (curentByte == stringPrefix)
                {
                    str.Append(stringPrefix + "0000");
                }
                else
                {
                    foreach (var item in substrings)
                    {
                        foreach (var subString in item)
                        {
                            var firstIndex = subString.Value.First();
                            var subStringLength = subString.Key.Length;
                            for (int j = 1; j < subString.Value.Count; j++)
                            {
                                if (subString.Value[j] == i)
                                {
                                    int S = subString.Value[j] - firstIndex;
                                    int L = subStringLength;
                                    long code = (prefix << 16) + (L << 10) + (S & 0b1111111111);
                                    if(code == 10493952)
                                    {
                                        Console.WriteLine("0");
                                    }
                                    str.Append(code.ToString("X6"));
                                    i += subStringLength - 2;
                                    isSequence = true;
                                }
                            }
                        }
                    }
                    if (!isSequence)
                    {
                        str.Append(curentByte);
                    }
                }
            }
            return str.ToString();
        }

        private static void RemoveRepeatInex(List<Dictionary<string, List<int>>> substrings)
        {
            HashSet<int> indexes = new HashSet<int>(100);
            for (int i = 0; i < substrings.Count; i++)
            {
                foreach (var item in substrings[i])
                {
                    for (int j = 0; j < item.Value.Count && item.Value.Count > 1; j++)
                    {
                        int value = item.Value[j];
                        if (!indexes.TryGetValue(value, out int index))
                        {
                            for (int k = 0; k < item.Key.Length; k++)
                            {
                                indexes.Add(k + value);
                            }
                        }
                        else
                        {
                            item.Value.Remove(index);
                            j--;
                        }
                    }
                    if (item.Value.Count <= 1)
                    {
                        substrings[i].Remove(item.Key);
                    }
                }
                if (substrings[i].Count == 0)
                {
                    substrings.Remove(substrings[i]);
                    i--;
                }
            }
        }

        private static byte[] ConvertStringToBytes(string inputString)
        {
            byte[] bytes = new byte[inputString.Length / 2];
            for (int i = 0; i < inputString.Length - 1; i += 2)
            {
                string currentByte = inputString[i..(i + 2)];
                bytes[i / 2] = Convert.ToByte(currentByte, 16);
            }
            return bytes;
        }

        private static StringBuilder ConvertBytesToString(List<byte> data)
        {
            StringBuilder stringBuilder = new StringBuilder(data.Count * 2);
            foreach (var item in data)
            {
                stringBuilder.Append(item.ToString("X2"));
            }
            return stringBuilder;
        }
    }
}
