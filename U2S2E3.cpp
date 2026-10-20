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

int GCFOfThree (int one, int two, int three)
{
    return greatestComFactor(greatestComFactor(one, two), three);
}

int main()
{
    int one;
    cout << "Enter a number: " << endl;
    cin >> one;

    int two;
    cout << "Enter another number: " << endl;
    cin >> two;

    int three;
    cout << "Enter a third number: " << endl;
    cin >> three;

    int result = GCFOfThree(one, two, three);
    
    cout << "The greatest common factor of " << one << ", " << two << ", and " << three << " is " << result << endl;
    return 0; 

}