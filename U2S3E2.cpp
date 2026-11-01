#include <iostream>

using namespace std;

unsigned long long factorial(int n) 
{
    if (n < 0) return 0;
    
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) 
    {
        result *= i;
    }
    return result;
}

int main() 
{
    int num;
    cout << "Enter a non-negative integer: ";
    cin >> num;
    
    cout << "The factorial of " << num << " is " << factorial(num) << endl;
    return 0;
}