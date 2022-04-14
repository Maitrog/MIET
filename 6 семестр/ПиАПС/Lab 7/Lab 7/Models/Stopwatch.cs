using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Timers;

namespace Lab_7.Models
{
    internal class Stopwatch: INotifyPropertyChanged
    {
        private Timer _timer;
        private static Stopwatch? _instance;
        private int _elapsed = 0;

        public event PropertyChangedEventHandler? PropertyChanged;

        public int Elapsed
        {
            get
            {
                return _elapsed;
            }
            set
            {
                if (value >= 0)
                {
                    _elapsed = value;
                    NotifyPropertyChanged(nameof(Elapsed));
                }
            }
        }
        private Stopwatch()
        {
            _timer = new Timer(1000);
            _timer.Elapsed += OnTimerElapsed;
        }

        private void NotifyPropertyChanged([CallerMemberName] string propertyName = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        private void OnTimerElapsed(object? sender, ElapsedEventArgs e)
        {
            Elapsed++;
        }

        public static Stopwatch GetInstance() 
        {
            if(_instance == null)
            {
                _instance = new Stopwatch();
            }
            return _instance;
        }

        public void Start()
        {
            _timer.Start();
        }

        public void Stop()
        {
            _timer.Stop();
        }

        public void Reset()
        {
            Elapsed = 0;
        }
    }
}
