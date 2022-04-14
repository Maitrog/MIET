using Lab_7.Models;
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace Lab_7
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        readonly Field field = new Field();
        readonly Stopwatch _stopwatch = Stopwatch.GetInstance();
        public MainWindow()
        {
            InitializeComponent();
            DataContext = _stopwatch;
            Loaded += MainWindow_Loaded;
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            for (int i = 0; i < field.Properties.Row; i++)
            {
                Field.RowDefinitions.Add(new RowDefinition());
            }
            for (int i = 0; i < field.Properties.Column; i++)
            {
                Field.ColumnDefinitions.Add(new ColumnDefinition());
            }
            RestartGame();
        }

        private void Cell_Click(object sender, RoutedEventArgs e)
        {
            Button buttonSender = sender as Button;
            int currentRow = Grid.GetRow(buttonSender);
            int currentColumn = Grid.GetColumn(buttonSender);

            if (!field.Cells[currentRow, currentColumn].IsMark)
            {
                if (field.Cells[currentRow, currentColumn].IsBomb)
                {
                    ShowBomb();
                    GameOver("YOU LOOOOSE");
                    return;
                }

                field.Cells[currentRow, currentColumn].Click();
                foreach (Button button in Field.Children)
                {
                    currentRow = Grid.GetRow(button);
                    currentColumn = Grid.GetColumn(button);
                    if (field.Cells[currentRow, currentColumn].IsOpen && !field.Cells[currentRow, currentColumn].IsBomb)
                    {
                        int bombCount = field.Cells[currentRow, currentColumn].GetBombCount();
                        if (bombCount == 0)
                        {
                            button.IsEnabled = false;
                            button.Content = new TextBlock();
                            field.Cells[currentRow, currentColumn].IsMark = false;
                        }
                        else
                        {
                            Brush color = Brushes.Black;
                            switch (bombCount)
                            {
                                case 1: color = Brushes.Blue; break;
                                case 2: color = Brushes.Green; break;
                                case 3: color = Brushes.Red; break;
                                case 4: color = Brushes.Purple; break;
                                case 5: color = Brushes.Yellow; break;
                            }
                            button.Content = new TextBlock() { Text = bombCount.ToString(), FontWeight = FontWeights.Bold, Foreground = color };
                        }
                    }
                }

                if (field.IsWin())
                {
                    GameOver("YOU WIN");
                }
            }
        }

        private void SetFlag_Click(object sender, MouseButtonEventArgs e)
        {
            Button buttonSender = sender as Button;
            int currentRow = Grid.GetRow(buttonSender);
            int currentColumn = Grid.GetColumn(buttonSender);

            field.Cells[currentRow, currentColumn].IsMark = !field.Cells[currentRow, currentColumn].IsMark;
            if (!field.Cells[currentRow, currentColumn].IsOpen)
            {
                if (field.Cells[currentRow, currentColumn].IsMark)
                {
                    buttonSender.Content = new TextBlock { Text = "🚩", Foreground = Brushes.Red };
                }
                else
                {
                    buttonSender.Content = new TextBlock { Text = "", Foreground = Brushes.Red };
                }
            }
        }

        private void RestartGame()
        {
            ClearField();
            CreateField();
            _stopwatch.Reset();
            _stopwatch.Start();
        }

        private void ClearField()
        {
            Field.Children.Clear();
            field.Clear();
        }

        private void CreateField()
        {
            field.FillBomb();
            for (int i = 0; i < field.Properties.Row; i++)
            {
                for (int j = 0; j < field.Properties.Column; j++)
                {
                    Button button = new Button();
                    button.Click += new RoutedEventHandler(Cell_Click);
                    button.MouseRightButtonDown += new MouseButtonEventHandler(SetFlag_Click);
                    Field.Children.Add(button);
                    Grid.SetRow(button, i);
                    Grid.SetColumn(button, j);
                    field.SubscribeObservers(i, j);
                }
            }
        }

        private void GameOver(string message = "GAME OVER")
        {
            _stopwatch.Stop();
            if (MessageBox.Show(message) == MessageBoxResult.OK)
            {
                RestartGame();
            }
        }

        private void ShowBomb()
        {

            foreach (Button button in Field.Children)
            {
                int currentRow = Grid.GetRow(button);
                int currentColumn = Grid.GetColumn(button);
                if (field.Cells[currentRow, currentColumn].IsBomb && !field.Cells[currentRow, currentColumn].IsMark)
                {
                    button.Content = new TextBlock() { Text = "💣" };
                }
                if (!field.Cells[currentRow, currentColumn].IsBomb && field.Cells[currentRow, currentColumn].IsMark)
                {
                    button.Content = new TextBlock() { Text = "❌", Foreground = Brushes.Red };
                }
            }
        }
    }
}
