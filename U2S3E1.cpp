#include <iostream>
#include <vector>

using namespace std;

int recursive(int one)
{
    if (one > 50)
    {
        return 0;
    }
    cout << one << endl; 
    return recursive(one + 1);

}

int main()
{
    recursive(1);
    return 0; 
}