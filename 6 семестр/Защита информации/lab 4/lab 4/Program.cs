using lab_4;
using System.Text;

string myKey = "687AFB5464569";
Blowfish blowfish = new(myKey);
Encoding utf8 = Encoding.UTF8;

string text = "s";

var encode = blowfish.Encode(utf8.GetBytes(text));
Console.WriteLine(utf8.GetString(encode));

var decode = blowfish.Decode(encode);
Console.WriteLine(utf8.GetString(decode));
