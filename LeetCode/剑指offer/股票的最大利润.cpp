// 假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖该股票一次可能获得的最大利润是多少？
#include <vector>
#include <numeric>
using namespace std;

int maxProfit(vector<int>& prices) {
    if(prices.empty())
        return 0;
    vector<int> diff;
    for(int i = 0; i < prices.size() - 1; i++) {
        diff.push_back(prices[i + 1] - prices[i]);
    }
    int max = 0;
    int sum = 0;
    for(auto it: diff) {
        sum += it;
        if(sum > max)
            max = sum;
        if(sum < 0)
            sum = 0;
    }
    
    return max;
}