using System.Windows.Media;

namespace lab_4_wpf.Models
{
    public class ProxyPicture : IPicture
    {
        private string _filePath;
        private RealPicture _realPicture;
        
        public ProxyPicture(string path)
        {
            _filePath = path;
        }
        public ImageBrush GetImage()
        {
            if(_realPicture == null)
            {
                _realPicture = new RealPicture(_filePath);
            }
            return _realPicture.GetImage();
        }
    }
}
