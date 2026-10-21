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

float averageVectors(vector<float> vec)
{
    float sum = 0.0f;
    for(int i = 0; i < vec.size(); i++)
    {
        sum += vec[i];
    }
    return sum / vec.size();

}

double averageVectors(vector<double> vec)
{
    double sum = 0.0;
    for(int i = 0; i < vec.size(); i++)
    {
        sum += vec[i];
    }
    return sum / vec.size();

}

int main()
{
    vector<int> integers = {1, 2, 3, 4, 5};
    vector<float> floats = {1.5f, 2.25f, 3.75f};
    vector<double> doubles = {1.25, 2.5, 3.75};

    cout << averageVectors(integers) << endl;
    cout << averageVectors(floats) << endl;
    cout << averageVectors(doubles) << endl;
    return 0;

}