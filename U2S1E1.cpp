#include <vector>
#include <iostream>

using namespace std;

int sumVectors(vector<int> vec)
{
    int sum = 0;
    for(int i = 0; i < vec.size(); i++)
    {
        sum += vec[i];
    }
    return sum;
}

int main()
{
    vector <int> numbers = {1, 2, 3, 4, 5};
    cout << "The sum of the vector elements is: " << sumVectors(numbers) << endl;
    return 0;
}