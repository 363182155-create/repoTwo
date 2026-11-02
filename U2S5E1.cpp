#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> my2DVector = {
    {1, 3, 5, 7, 9},
    {11, 13, 15, 17, 19},
    {21, 23, 25, 27, 29},
    {31, 33, 35, 37, 39},
    {41, 43, 45, 47, 49},
    {51, 53, 55, 57, 59},
    {61, 63, 65, 67, 69},
    {71, 73, 75, 77, 79},
    {81, 83, 85, 87, 89},
    {91, 93, 95, 97, 99}
    
};

void printRow(vector<int> row)
{
    for (int i = 0; i < row.size(); i++)
    {
        cout << row[i] << " ";
    }
    cout << endl;
}

int main()
{
    cout << "My 2D vector: " << endl;

    for (int i = 0; i < my2DVector.size(); i++)
    {
        printRow(my2DVector[i]);
    }

    return 0;
}