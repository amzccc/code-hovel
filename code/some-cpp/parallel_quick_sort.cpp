#include <iostream>
#include <vector>
#include <future>
#include <random>
#include <chrono>

using namespace std;

template<typename T>
void quick_sort(vector<T>& vec, int begin, int end) {
    if(begin >= end) {
        return;
    }
    auto tmp = (end - begin) / 2 + vec.begin();
    *tmp > vec[end] ? swap(*tmp, vec[end]) : swap(*tmp, *tmp);
    int l = begin;
    int r = end;
    T base = vec[end];
    while(l < r) {
        while(l < r && vec[l] < base) {
            l++;
        }
        while(l < r && vec[r] >= base) {
            r--;
        }
        swap(vec[l], vec[r]);
    }
    swap(vec[l], vec[end]);
    // for(auto& elem : vec) {
    //     cout << elem << '\t';
    // }
    // cout << endl;
    quick_sort(vec, begin, l - 1);
    quick_sort(vec, l + 1, end);
}

template<typename T>
void parallel_quick_sort(vector<T>& vec, int begin, int end) {
    if(begin >= end) {
        return;
    }
    auto tmp = (end - begin) / 2 + vec.begin();
    *tmp > vec[end] ? swap(*tmp, vec[end]) : swap(*tmp, *tmp);
    int l = begin;
    int r = end;
    T base = vec[end];
    while(l < r) {
        while(l < r && vec[l] < base) {
            l++;
        }
        while(l < r && vec[r] >= base) {
            r--;
        }
        swap(vec[l], vec[r]);
    }
    swap(vec[l], vec[end]);
    if(end - begin < 1000000) {
        quick_sort(vec, begin, l - 1);
        quick_sort(vec, l + 1, end);
    }
    else {
        auto f1 = async(launch::async, parallel_quick_sort<T>, ref(vec), begin, l - 1);
        auto f2 = async(launch::async, parallel_quick_sort<T>, ref(vec), l + 1, end);
        f1.get();
        f2.get();
    }
    
}

int main() {
    random_device seed;
    default_random_engine eng(seed());
    uniform_int_distribution<long long> ud(0, 100000000);
    vector<long long> vec;
    vector<long long> vec2;
    for(int i = 0; i < 100000000; i++) {
        long long tmp = ud(eng);
        vec.emplace_back(tmp);
        vec2.emplace_back(tmp);
    }
    chrono::steady_clock::time_point start;
    chrono::steady_clock::time_point end;

    start = chrono::steady_clock::now();
    quick_sort(vec, 0, vec.size() - 1);
    end = chrono::steady_clock::now();
    cout << "quick_sort time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;

    start = chrono::steady_clock::now();
    parallel_quick_sort(vec2, 0, vec2.size() - 1);
    end = chrono::steady_clock::now();
    cout << "parallel_quick_sort time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
    cout << endl;
    
    return 0;
}
