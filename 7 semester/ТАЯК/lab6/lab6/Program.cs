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

PrintTag(firstTag);

void InitTags(XmlElement xmlElement, BasedTag parent)
{
    int defaultWidth = xmlElement.ChildNodes.Count > 0 ? 80 / xmlElement.ChildNodes.Count : parent.Width;
    int defaultHeight = xmlElement.ChildNodes.Count > 0 ? 24 / xmlElement.ChildNodes.Count : parent.Height;
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

void PrintTag(BasedTag parent)
{
    foreach (var item in parent.Children)
    {
        if (item is ColumnTag column)
        {
            Console.ForegroundColor = (ConsoleColor)column.TextColor;
            Console.BackgroundColor = (ConsoleColor)column.BgColor;
            Console.WriteLine($"Foreground color set to {column.TextColor}");
        }
        PrintTag(item);
    }
}