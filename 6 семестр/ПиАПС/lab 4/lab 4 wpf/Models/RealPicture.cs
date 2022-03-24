using System;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace lab_4_wpf.Models
{
    public class RealPicture : IPicture
    {
        public ImageBrush RealImageBrush { get; private set; }
        public RealPicture(string path)
        {
            RealImageBrush = new ImageBrush();
            RealImageBrush.ImageSource = new BitmapImage(new Uri(path, UriKind.Absolute));
        }
        public ImageBrush GetImage()
        {
            return RealImageBrush;
        }
    }
}
