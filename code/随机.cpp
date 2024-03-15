#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

template <typename T1, typename T2>
void distr(T1 d, T2 e, const string &name) {
    //打印最大最小值和四个参考值
    cout << name << ": " << endl;
    cout << "-min(): "  <<d.min() << endl;
    cout << "-max(): "  <<d.max() << endl;
    cout << "-value: " << d(e) << " " << d(e) << " " << d(e) << " " << d(e) << endl;
    //以整数记录产生的值
    map<long long, int> valuecounter;
    for (int i = 0; i < 200000; i++) {
        valuecounter[d(e)]++;
    }
    //打印分布
    cout << "====" << endl;
    for(auto elem: valuecounter) {
        cout << setw(3) << elem.first <<": " << elem.second << endl;
    }
    cout << "====" << endl;
    cout << endl;
}

int main() 
{
    //随机引擎  注意引擎的初始状态是明确定义的  STL中预定义了16种随机引擎
    default_random_engine eng;
    //线性随机
    uniform_int_distribution<int> di(10, 20);
    for(int i = 0; i < 10; i++) {
        cout << di(eng) << " ";
    }
    cout << endl;
    uniform_real_distribution<double> dr(10, 20);
    for(int i = 0; i < 10; i++) {
        cout << dr(eng) << " ";
    }
    cout << endl;
    //使用引擎打乱数组
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    shuffle(v.begin(), v.end(), eng);
    for(auto it: v) {
        cout << it << " ";
    }
    cout << endl;
    

/*STL中的分布
    均匀分布            uniform_int_distribution                int
                        uniform_real_distribution               real
    伯努利分布          bernoulli_distribution                  bool
                        binomial_distribution                   int
                        geometric_distribution                  int
                        negative_binomial_distribution          int
    泊松分布            poisson_distribution                    int
                        exponential_distribution                real
                        gamma_distribution                      real
                        weibull_distribution                    real
                        extreme_value_distribution              real
    正太分布            normal_distribution                     real
                        lognormal_distribution                  real
                        chi_squared_distribution                real
                        cauchy_distribution                     real
                        fisher_f_distribution                   real
                        student_t_distribution                  real
    抽样分布            discrete_distribution                   int
                        piecewise_constant_distribution         real
                        piecewise_linear_distribution           real
*/
knuth_b e;
uniform_real_distribution<> ud(0, 10);
distr(ud, e, "uniform_real_distribution");

normal_distribution<>  nd;
distr(nd, e, "normal_distribution");

exponential_distribution<> ed;
distr(ed, e, "exponential_distribution");

gamma_distribution<> gd;
distr(gd, e, "gamma_distribution");
}