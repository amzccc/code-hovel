#include <iostream>
#include <vector>

using namespace std;

vector<int> printNumbers(int n)
{
    vector<int> result;
    int count = 1;
    for(; n > 0; n--)
    {
        count *= 10;
    }
    for(int i = 1; i < count; i++)
        result.push_back(i);
    return result;
}