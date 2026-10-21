#include <iostream>
#include <vector>

using namespace std;

int gcdOfTwo(int one, int two)
{
    while (two != 0)
    {
        int remainder = one % two;
        one = two;
        two = remainder;
    }
    return one;
}

int greatestComFactor(const vector<int>& numbers)
{
    if (numbers.empty())
    {
        return 0;
    }
    int gcf = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i)
    {
        gcf = gcdOfTwo(gcf, numbers[i]);
    }
    return gcf;
}

int main()
{
    int one;
    cout << "Enter a number: " << endl;
    cin >> one;

    int two;
    cout << "Enter another number: " << endl;
    cin >> two;

    cout << "The greatest common factor of " << one << " and " << two << " is " << greatestComFactor({one, two}) << endl;
    return 0; 

}