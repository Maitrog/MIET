using lab_4_wpf.Models;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace lab_4_wpf
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Point _startMousePosition;
        Point _startBorderPosition;
        bool _mouseCapture = false;
        bool _mouseRightButtonDown = false;
        IPicture _picture;

        public MainWindow()
        {
            InitializeComponent();
            _picture = new ProxyPicture("C:/Users/Mihay/Documents/1599737054127349264.png");
        }

        private void myBorder_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            Border border = (Border)sender;

            _startMousePosition = Mouse.GetPosition(this);
            MatrixTransform tr = (MatrixTransform)border.RenderTransform;
            _startBorderPosition = new Point(tr.Matrix.OffsetX, tr.Matrix.OffsetY);

            border.CaptureMouse();
            _mouseCapture = true;
        }

        private void myBorder_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            Border border = (Border)sender;
            border.ReleaseMouseCapture();

            _mouseCapture = false;
        }

        private void myBorder_MouseMove(object sender, MouseEventArgs e)
        {
            if (_mouseCapture == true)
            {
                var mousePosition = Mouse.GetPosition(this);

                Border border = (Border)sender;
                border.RenderTransform = new MatrixTransform
                {
                    Matrix = new Matrix()
                    {
                        M11 = 1,
                        M22 = 1,
                        OffsetX = _startBorderPosition.X + (mousePosition.X - _startMousePosition.X),
                        OffsetY = _startBorderPosition.Y + (mousePosition.Y - _startMousePosition.Y)
                    }
                };
            }
        }

        private void myBorder_MouseRightButtonDown(object sender, MouseButtonEventArgs e)
        {
            _mouseRightButtonDown = true;
        }

        private void myBorder_MouseRightButtonUp(object sender, MouseButtonEventArgs e)
        {
            if(_mouseRightButtonDown == true)
            {
                myBorder.Background = _picture.GetImage();
            }
            _mouseRightButtonDown = false;
        }
    }
}
