#include <iostream>
#include "header.h"

using namespace std;

int main()
{
    cout << "Test Data: " << endl;

    for (int i=0; i < vectorData.size(); i++)
    {
        cout << vectorData[i] << " ";
    }

    cout << endl;
    return 0;
}