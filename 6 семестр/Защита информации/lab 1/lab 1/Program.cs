const string doc_file = "./Data/test_doc.doc";
const string docx_file = "./Data/test_docx.docx";
const string jpg_file = "./Data/test_jpg.jpg";
const string mp4_file = @"C:\Users\Mihay\Documents\Фото\Мемы\Джиган даёт совет тем, кто сейчас на чиле [NR.Music].mp4";

string path = doc_file;
/// <summary>
/// Exercise 1
/// </summary>
FileInfo file = new FileInfo(path);
Console.WriteLine(file.Length);


/// <summary>
/// Exercise 2
/// </summary>
int[] bytes = new int[256];
using (FileStream fs = File.Open(path, FileMode.Open))
{
    while (true)
    {
        int rByte = fs.ReadByte();
        if(rByte == -1)
        {
            break;
        }
        bytes[rByte] += 1;
    }
}
for(int i = 0; i < bytes.Length; i++)
{
    Console.WriteLine($"{i}: {(double)bytes[i]/file.Length}");
}

/// <summary>
/// https://randomus.ru/quick?from=0&to=255&count=256&norepeat=1 - генератор последовательности
/// Exercise 3
/// </summary>
// ENCODE
int[] key = GetKey();
using (FileStream fs = File.Open(path, FileMode.Open))
{
    FileStream encodeFs = File.Create("./Data/encode");
    while (true)
    {
        int rByte = fs.ReadByte();
        if (rByte == -1)
        {
            break;
        }
        encodeFs.WriteByte((byte)key[rByte]);
    }
    encodeFs.Close();
}
Console.WriteLine("Encode success");

// DECODE
using(FileStream fs = File.Open("./Data/encode", FileMode.Open))
{
    FileStream decodeFs = File.Create("./Data/decode");
    while (true)
    {
        int rByte = fs.ReadByte();
        if (rByte == -1)
        {
            break;
        }
        decodeFs.WriteByte((byte)Array.IndexOf(key, rByte));
    }
    decodeFs.Close();
}
Console.WriteLine("Decode success");


int[] GetKey()
{
    int counter = 0;
    int[] key = new int[256];
    foreach (string line in File.ReadLines("./Data/key.txt"))
    {
        key[counter] = int.Parse(line);
        counter++;
    }
    return key;
}