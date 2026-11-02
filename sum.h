#include <vector>

using namespace std;

int findSum(vector<int> numbers)
{
    int total = 0;

    for (int i = 0; i < numbers.size(); i++) //
    {
        total = total + numbers[i];
    }

    return total;
}