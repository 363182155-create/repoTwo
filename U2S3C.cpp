#include <iostream>

using namespace std;

unsigned int fibonacci(unsigned int num)
{
    if (num <= 0)
        
        return 0;

    else if (num == 1)

        return 1;

    else

        return fibonacci(num - 1) + fibonacci(num - 2);
}

int main()
{
    unsigned int num;

    cout << "Enter a positive integer: ";
    cin >> num;

    cout << "Fibonacci sequence up to " << num << " terms:" << endl;

    for (unsigned int i = 0; i < num; i++)
    {
        cout << fibonacci(i) << " ";
    }
    
    cout << endl;

    return 0;
}
