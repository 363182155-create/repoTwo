#include <iostream>
#include <vector>

using namespace std;

int greatestComFactor(int one, int two)
{
    while (two != 0)
    {
        int remainder = one % two;
        one = two;
        two = remainder;
    }
    return one;
}

int main()
{
    int one;
    cout << "Enter a number: " << endl;
    cin >> one;

    int two;
    cout << "Enter another number: " << endl;
    cin >> two;

    cout << "The greatest common factor of " << one << " and " << two << " is " << greatestComFactor(one, two) << endl;
    return 0; 

}