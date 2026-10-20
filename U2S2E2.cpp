#include <iostream>
#include <vector>

using namespace std;

int averageVectors(vector<int> vec)
{
    int sum = 0;
    for(int i = 0; i < vec.size(); i++)
    {
        sum += vec[i];
    }
    return sum / vec.size();

}

int main()
{
    vector <int> numbers = {1, 2, 3, 4, 5};
    cout << averageVectors(numbers) << endl;
    return 0;

}