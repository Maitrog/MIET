#include <iostream>
#include <random>

using namespace std;

int main()
{
    random_device rd;
    mt19937 mersenne(rd());

    for (int count = 0; count < 50000; ++count)
    {
        cout << mersenne()%100 << "\t";

        // Если вывели 5 чисел, то вставляем символ новой строки
        //if ((count + 1) % 5 == 0)
          //  cout << "\n";
    }
    system("pause");
}
