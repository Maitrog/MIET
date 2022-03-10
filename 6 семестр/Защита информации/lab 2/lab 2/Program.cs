using lab_2;

RSA44 rsa = new();
string str = "ПРивет мир";

List<int> encodeStr = rsa.Encode(str);
string decodeStr = rsa.Decode(encodeStr);

Console.WriteLine($"Open key: {rsa.GetOpenKey()}");
Console.WriteLine($"Close key: {rsa.GetCloseKey()}");
Console.WriteLine(string.Join(" ", encodeStr));
Console.WriteLine(decodeStr);
Console.WriteLine(RSA44.Decode(encodeStr, rsa.GetCloseKey()));