using lab6.Enums;
using lab6.Tags;
using System.Data.Common;
using System.Drawing;
using System.Xml;
using System.Xml.Linq;
using System.Xml.Serialization;

const string eMarkPath = "C:\\Users\\Mihay\\Documents\\MIET\\7 semester\\ТАЯК\\ТАЯК\\Laba6\\test.txt";
string text = File.ReadAllText(eMarkPath);

XmlDocument xmlDoc = new();

xmlDoc.LoadXml(text);

var block = xmlDoc.DocumentElement;
BlockTag firstTag = new();

InitTags(block, firstTag);

PrintTag(firstTag, 0, 0);

void InitTags(XmlElement xmlElement, BasedTag parent)
{
    int w = parent != null ? parent.Width : 80;
    int h = parent != null ? parent.Height : 24;
    int childeCount = xmlElement.ChildNodes.Count;
    int defaultWidth = childeCount > 0 ? w / childeCount : w;
    int defaultHeight = childeCount > 0 ? h / childeCount : h;
    foreach (var item in xmlElement.ChildNodes)
    {
        Halign? halign = null;
        Valign? valign = null;
        int? textColor = null;
        int? bgColor = null;
        int? height = null;
        int? width = null;
        int? columns = null;
        int? rows = null;
        if (item is XmlElement nextXmlElement)
        {
            if (nextXmlElement.GetAttribute("Columns") is not "")
            {
                columns = int.Parse(nextXmlElement.GetAttribute("Columns"));
            }
            if (nextXmlElement.GetAttribute("Rows") is not "")
            {
                rows = int.Parse(nextXmlElement.GetAttribute("Rows"));
            }
            if (nextXmlElement.GetAttribute("TextColor") is not "")
            {
                textColor = int.Parse(nextXmlElement.GetAttribute("TextColor"));
            }
            if (nextXmlElement.GetAttribute("BgColor") is not "")
            {
                bgColor = int.Parse(nextXmlElement.GetAttribute("BgColor"));
            }
            if (nextXmlElement.GetAttribute("Height") is not "")
            {
                height = int.Parse(nextXmlElement.GetAttribute("Height"));
            }
            if (nextXmlElement.GetAttribute("Width") is not "")
            {
                width = int.Parse(nextXmlElement.GetAttribute("Width"));
            }
            if (nextXmlElement.GetAttribute("Valign") is not "")
            {
                valign = (Valign)Enum.Parse(typeof(Valign), nextXmlElement.GetAttribute("Valign"));
            }
            if (nextXmlElement.GetAttribute("Halign") is not "")
            {
                halign = (Halign)Enum.Parse(typeof(Halign), nextXmlElement.GetAttribute("Halign"));
            }

            if (nextXmlElement.Name.ToLower() == "column")
            {
                ColumnTag column = new(parent, width ?? defaultWidth, height ?? parent.Height)
                {
                    Valign = valign ?? Valign.Top,
                    Halign = halign ?? Halign.Left,
                    BgColor = bgColor ?? 0,
                    TextColor = textColor ?? 15,
                };

                w -= column.Width;
                childeCount--;
                defaultWidth = childeCount > 0 ? w / childeCount : w;


                InitTags(nextXmlElement, column);
                parent.Children.Add(column);
            }
            else if (nextXmlElement.Name.ToLower() == "row")
            {
                RowTag row = new(parent, width ?? parent.Width, height ?? defaultHeight)
                {
                    Valign = valign ?? Valign.Top,
                    Halign = halign ?? Halign.Left,
                    BgColor = bgColor ?? 0,
                    TextColor = textColor ?? 15,
                };

                h -= row.Height;
                childeCount--;
                defaultHeight = childeCount > 0 ? h / childeCount : h;

                InitTags(nextXmlElement, row);
                parent.Children.Add(row);
            }
            else if (nextXmlElement.Name.ToLower() == "block")
            {
                BlockTag block = new(parent, width ?? parent.Width, height ?? defaultHeight)
                {
                    Columns = columns ?? 1,
                    Rows = rows ?? 0,
                };

                InitTags(nextXmlElement, block);
                parent.Children.Add(block);
            }
        }
        else if (item is XmlText text)
        {
            parent.Text = text.Value;
        }
    }
}

void PrintTag(BasedTag parent, int startColumn, int startRow)
{
    int topPosition = startRow;
    int leftPosition = startColumn;
    foreach (var item in parent.Children)
    {
        if (item is ColumnTag column)
        {
            if (!string.IsNullOrEmpty(column.Text))
            {
                Console.ForegroundColor = (ConsoleColor)column.TextColor;
                Console.BackgroundColor = (ConsoleColor)column.BgColor;
                var strings = GetStrings(column.Text,
                  column.Width, column.Height, column.Valign, column.Halign);
                for (int i = 0; i < strings.Count; i++)
                {
                    string? item2 = strings[i];
                    Console.SetCursorPosition(leftPosition, topPosition + i);
                    Console.WriteLine(item2);
                }
                PrintTag(item, leftPosition, topPosition);
                leftPosition += column.Width;
            }
            else
            {
                PrintTag(item, leftPosition, topPosition);
                leftPosition += column.Width;
            }
        }
        if (item is RowTag row)
        {
            if (!string.IsNullOrEmpty(row.Text))
            {
                Console.ForegroundColor = (ConsoleColor)row.TextColor;
                Console.BackgroundColor = (ConsoleColor)row.BgColor;
                var strings = GetStrings(row.Text,
                    row.Width, row.Height, row.Valign, row.Halign);
                for (int i = 0; i < strings.Count; i++)
                {
                    string? item2 = strings[i];
                    Console.SetCursorPosition(leftPosition, topPosition + i);
                    Console.WriteLine(item2);
                }
                PrintTag(item, leftPosition, topPosition);
                topPosition += row.Height;
            }
            else
            {
                PrintTag(item, leftPosition, topPosition);
                topPosition += row.Height;
            }
        }
        if (item is BlockTag)
        {
            PrintTag(item, startColumn, startRow);
        }
    }
}

List<string> GetStrings(string inputText, int width, int height, Valign valign, Halign halign)
{
    List<string> result = new();
    int stringCount = (int)Math.Ceiling((double)inputText.Length / width);
    string emptyStr = new string(' ', width);
    int addString = height - stringCount;

    if (addString > 0 && valign == Valign.Bottom)
    {
        for (int i = 0; i < addString; i++)
        {
            result.Add(emptyStr);
        }
    }

    if (addString / 2 > 0 && valign == Valign.Center)
    {
        for (int i = 0; i < addString / 2; i++)
        {
            result.Add(emptyStr);
        }
    }

    for (int i = 0; i < inputText.Length;)
    {
        int length = inputText.Length - i >= width ? width : inputText.Length - i;
        string str = inputText.Substring(i, length);
        i += length;
        switch (halign)
        {
            case Halign.Left:
                str = str.PadRight(width, ' ');
                break;
            case Halign.Right:
                str = str.PadLeft(width, ' ');
                break;
            case Halign.Center:
                str = str.PadLeft(width - (width - str.Length) / 2, ' ');
                str = str.PadRight(width, ' ');
                break;
        }
        result.Add(str);
    }

    if (addString - addString / 2 > 0 && valign == Valign.Center)
    {
        for (int i = 0; i < addString - addString / 2; i++)
        {
            result.Add(emptyStr);
        }
    }

    if (addString > 0 && valign == Valign.Top)
    {
        for (int i = 0; i < addString; i++)
        {
            result.Add(emptyStr);
        }
    }

    return result;
}