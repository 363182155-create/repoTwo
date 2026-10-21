#include <vector>
#include <iostream>

using namespace std;

int sumVectors(vector<int> vec)
{
    int sum = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        sum += vec[i];
    }
    return sum;
}

float sumVectors(vector<float> vec)
{
    float sum = 0.0f;
    for (int i = 0; i < vec.size(); i++)
    {
        sum += vec[i];
    }
    return sum;
}

double sumVectors(vector<double> vec)
{
    double sum = 0.0;
    for (int i = 0; i < vec.size(); i++)
    {
        sum += vec[i];
    }
    return sum;
}

int main()
{
    vector<int> integers = {1, 2, 3, 4, 5};
    vector<float> floats = {1.5f, 2.25f, 3.75f};
    vector<double> doubles = {1.25, 2.5, 3.75};

    cout << "Int sum: " << sumVectors(integers) << endl;
    cout << "Float sum: " << sumVectors(floats) << endl;
    cout << "Double sum: " << sumVectors(doubles) << endl;

    return 0;
}