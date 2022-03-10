using System.Text;

const string path = @"C:\Users\Mihay\Documents\MIET\6 семестр\Защита информации\Laboratornaya_rabota_3_variantyi\Лабораторная работа 3_варианты\5.bmp";
DecodeLSB(path);


EncodeLSB("Закодированное сообщение. Encoded message", "./1.bmp");
DecodeLSB("./1.bmp", "./myMsg.txt");

byte[] ClearHightBytes(byte[] buffer)
{
    for (int i = 0; i < buffer.Length; i++)
    {
        buffer[i] = (byte)(buffer[i] & 0b11);
    }
    return buffer;
}

void DecodeLSB(string imagePath, string resultPath = "./decodeMsg.txt")
{
    long seek;
    byte[] buffer = new byte[4];
    byte rByte = 0;

    using (FileStream fs = File.OpenRead(imagePath))
    {
        fs.Seek(10, SeekOrigin.Begin);
        fs.Read(buffer, 0, 4);
        seek = (buffer[3] << 24) + (buffer[2] << 16) + (buffer[1] << 8) + (buffer[0]);
        fs.Position = seek;

        FileStream decodeFs = File.Create(resultPath);
        while (true)
        {
            fs.Read(buffer, 0, 4);
            buffer = ClearHightBytes(buffer);
            rByte = (byte)((buffer[0] << 6) + (buffer[1] << 4) + (buffer[2] << 2) + (buffer[3]));
            if (rByte == 255)
            {
                break;
            }
            decodeFs.WriteByte(rByte);
        }
        decodeFs.Close();
    }
}

void EncodeLSB(string msg, string imagePath)
{
    long seek;
    byte[] buffer = new byte[4];

    using (FileStream fs = File.Open(imagePath, FileMode.Open))
    {
        fs.Seek(10, SeekOrigin.Begin);
        fs.Read(buffer, 0, 4);
        seek = (buffer[3] << 24) + (buffer[2] << 16) + (buffer[1] << 8) + (buffer[0]);

        fs.Position = seek;
        Encoding utf8 = Encoding.UTF8;
        byte[] byteMsg = utf8.GetBytes(msg);

        for (int i = 0; i < byteMsg.Length; i++)
        {
            fs.Read(buffer, 0, 4);
            buffer = EncodeByte(byteMsg[i], buffer);
            fs.Position -= 4;

            fs.Write(buffer, 0, buffer.Length);
        }
    }
}

byte[] EncodeByte(byte src, byte[] buffer)
{
    if (buffer.Length != 4)
    {
        throw new Exception();
    }
    for (int i = 0; i < 4; i++)
    {
        buffer[i] = (byte)(buffer[i] & 0b11111100);
        buffer[i] += (byte)((src & (int)(3 * Math.Pow(4, 3 - i))) >> ((3 - i) * 2));
    }
    return buffer;
}