using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_1.Singleton
{
    internal sealed class AppDb
    {
        private static AppDb? _appDbInstance;
        private AppDb() { }
        public static AppDb GetInstance()
        {
            if(_appDbInstance == null)
            {
                _appDbInstance = new AppDb();
            }
            return _appDbInstance;
        }
    }
}
