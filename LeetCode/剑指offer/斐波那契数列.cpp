#include <iostream>
using namespace std;

class Solution
{
public:
    int fib(int n)
    {
        if(n == 0)
            return 0;
        else if(n == 1)
            return 1;
        else
        {     
            int prepre = 0; 
            int pre = 1;
            int result = 0;
            for(int i = 2; i <= n; i++)
            {
                result = prepre + pre;
                prepre = pre;
                pre = result;
            }
            return result;
        }
    }
};

//test
int main()
{
    Solution s;
    cout << s.fib(45);
}