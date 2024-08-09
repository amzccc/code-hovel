// 输入整数数组 arr ，找出其中最小的 k 个数。
// 例如，输入4、5、1、6、2、7、3、8这8个数字，
// 则最小的4个数字是1、2、3、4。
#include <vector>
#include <iostream>
#include <memory>
using namespace std;

//超出时间 淦
/*
vector<int> getLeastNumbers(vector<int>& arr, int k){
    vector<int> result{};
    result.clear();
    if(arr.size() == 0 || k == 0)
        return {};
    result.push_back(arr[0]);
    if(arr.size() == 1 && k >= 1)
        return result;
    for(int i = 1; i < arr.size(); i++){    
        int count = result.size() - 1;
        while(count >= 0 && (result[count] > arr[i])){
            result.push_back({});
            result[count + 1] = result[count];
            count--;
        }
        result[count + 1] = arr[i];
        if(result.size() > k)
            result.resize(k);
    }
    return result;
}
*/
//还是挺慢
/*
vector<int> getLeastNumbers(vector<int>& arr, int k)
{   
    if(k == 0)
        return {};
    if(k >= arr.size())
        return arr;
    vector<int> result;
    for(int i = 0; i < k; i++)
        result.push_back(arr[i]);
    for(int i = k; i < arr.size(); i++)
    {   
        int index = 0;
        for(int j = 1; j < k; j++)
        {
            if(result[index] < result[j])
                index = j;
        }
        if(arr[i] < result[index])
            result[index] = arr[i];
    }
    return result;
}
*/

/*
void quick_sort(vector<int> &arr, int begin, int end, int k)
{
    if(begin >= end)
        return;
    int l_ptr = begin;
    int r_ptr = end;
    int base = end;
    while(l_ptr <= r_ptr)
    {
        if(l_ptr == r_ptr)
            break;
        while(l_ptr < r_ptr && arr[l_ptr] <= arr[base])
            l_ptr++;
        while(l_ptr < r_ptr && arr[r_ptr] >= arr[base])
            r_ptr--;
        int temp = arr[l_ptr];
        arr[l_ptr] = arr[r_ptr];
        arr[r_ptr] = temp;
    }
    swap(arr[base], arr[l_ptr]);
    if(l_ptr == k-1)
        return;
    quick_sort(arr, begin, l_ptr -1, k);
    quick_sort(arr, l_ptr + 1, end, k);
}

vector<int> getLeastNumbers(vector<int>& arr, int k)
{
    if(k == 0)
        return {};
    if(k >= arr.size())
        return arr;
    quick_sort(arr, 0, arr.size() - 1, k);
    vector<int> result(arr.begin(), arr.begin() + k);
    return result;
}
*/

//学习下dalao代码
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        if (k >= arr.size()) return arr;
        return quickSort(arr, k, 0, arr.size() - 1);
    }
private:
    vector<int> quickSort(vector<int>& arr, int k, int l, int r) {
        int i = l, j = r;
        while (i < j) {
            while (i < j && arr[j] >= arr[l]) j--;
            while (i < j && arr[i] <= arr[l]) i++;
            swap(arr[i], arr[j]);
        }
        swap(arr[i], arr[l]);
        if (i > k) return quickSort(arr, k, l, i - 1);
        if (i < k) return quickSort(arr, k, i + 1, r);
        vector<int> res;
        res.assign(arr.begin(), arr.begin() + k);
        return res;
    }
};

//test
int main()
{
    vector<int> vec{9, 7, 4, 2, 1};
    Solution s;
    vector<int> a = s.getLeastNumbers(vec, 2);
    for(auto it: a)
        cout << it << endl;
}
