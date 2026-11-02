#include "header.h"
#include "sum.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "Test Data: " << endl;

    for (int i=0; i < vectorData.size(); i++)
    {
        cout << vectorData[i] << " ";
    }

    cout << endl;

    cout << "Sum of vecotr values: " << findSum(vectorData) << endl;
    
    return 0;
}