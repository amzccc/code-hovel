#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <iterator>
#include <set>
#include <string>
#include <numeric>
#include <functional>

int main()
{
    using namespace std;
    //最大最小值
    vector<int> coll({2, 5, 4, 1, 6, 3});
    auto minpos = min_element(coll.begin(), coll.end());
    cout << "min: " << *minpos << endl;
    auto maxpos = max_element(coll.begin(), coll.end());
    cout << "max: " << *maxpos << endl;
    //排序
    sort(coll.begin(), coll.end());
    //找到特定值的位置
    auto pos3 = find(coll.begin(), coll.end(), 3);
    //逆序从3开始的位置
    reverse(pos3, coll.end());
    //打印
    for(auto &it: coll)
        cout << it << " ";
    cout << endl;
    //复制
    list<int> coll1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> coll2;
    coll2.resize(coll1.size());  //复制算法时，要保证目的对象的区间至少和源对象一样大
    copy(coll1.begin(), coll1.end(), coll2.begin());

    //迭代器的适配器  安插型迭代器
    deque<int> coll3;
    set<int> coll4;
    //安插型迭代器包含了插入操作
    copy(coll1.begin(), coll1.end(), back_inserter(coll3));     //后插
    copy(coll1.begin(), coll1.end(), front_inserter(coll3));    //前插
    copy(coll1.begin(), coll1.end(), inserter(coll4, coll4.begin()));   //普通插入

    //串流型迭代器
    vector<string> vec;
    copy(istream_iterator<string>(cin), istream_iterator<string>(),
            back_inserter(vec));
    sort(vec.begin(), vec.end());
    //unique_copy会删除相邻的重复值
    unique_copy(vec.begin(), vec.end(), ostream_iterator<string>(cout, "\n"));

    //使用迭代器的代价：无法通过迭代器操作修改容器
    list<int> li;
    for(int i = 6; i > 0; i--)
    {
        li.push_back(i);
        li.push_front(i);
    }
    copy(li.begin(), li.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    list<int>::iterator end = remove(li.begin(), li.end(), 3);  //remove不会改变容器大小，返回最后删除的元素的下一个位置
    copy(li.begin(), end, ostream_iterator<int>(cout, " "));   
    cout << endl;
    cout << "number of remove elements: " << distance(end, li.end()) << endl;
    cout << "remove but not erase: " << endl << "list: ";
    copy(li.begin(), li.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << "after erase: " << endl << "list: ";
    li.erase(end, li.end());
    copy(li.begin(), li.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    //STL算法
    /*
    _if: 接受一个自定义的查找准则；
    _copy: 表示不止元素被操作，还会被复制到标的区间
    */
   //非更易型算法
    vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> v2{2, 4, 10, 3, 18, 40, 31, 6};
    auto op = [&](int &a, int &b){return a < b;};
    int val = 42;
    vector<int>::iterator temp_ptr;
    count(v1.begin(), v1.end(), val);       //返回元素个数
    count_if(v1.begin(), v1.end(), op);         //返回满足某以准则的元素个数
    min_element(v1.begin(), v1.end());          //最小值
    max_element(v1.begin(), v1.end());          //最大值
    auto p = minmax_element(v1.begin(), v1.end());       //最小值和最大值
    find(v2.begin(), v2.end(), 42);         //查找与传入值相等的第一个元素
    find_if(v2.begin(), v2.end(), op);          //查找满足某个准则的第一个元素
    find_if_not(v2.begin(), v2.end(), op);           //查找不满足某个准则的第一个元素
    search(v1.begin(), v1.begin() + 3, v2.begin(), v2.end(), op);           //查找某个子区间的第一次出现的位置
    search_n(v2.begin(), v2.end(), 42, op);         //查找具备某个特性之前的n个连续元素
    find_end(v1.begin(), v1.begin() + 3, v2.begin(), v2.end(), op);         //查找某个子区间的最后一次出现的位置
    find_first_of(v1.begin(), v1.begin() + 3, v2.begin(), v2.end(), op);            //查找某个可能元素中的第一个出现者
    adjacent_find(v1.begin(), v1.end());            //查找连续两个相等或满足某准则的元素
    equal(v2.begin(), v2.end(), 42);            //判断相等
    is_permutation(v1.begin(), v1.end(), v2.begin());           //两个不定序区间元素是否含有相等元素（v2中是否含有v1的全部元素）
    mismatch(v1.begin(), v1.end(), v2.begin());         //返回两序列的各组对应元素中的第一对不相等元素
    lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());          //判断字典顺序下某序列是否小于另一序列
    is_sorted(v1.begin(), v1.end());            //判断是否已排序
    is_sorted_until(v2.begin(), v2.end());          //返回第一个不遵守某排序准则的元素
    is_partitioned(v1.begin(), v1.end(), op);           //判断区间是否基于某准则被分为两组
    partition_point(v1.begin(), v1.end(), op);          //返回区间第一个分割元素
    is_heap(v1.begin(), v1.end());          //判断是否为堆
    is_heap_until(v1.begin(), v1.end());            //返回第一个不是堆的元素
    all_of(v1.begin(), v1.end(), op);           //是否所有元素都满足某准则
    any_of(v1.begin(), v1.end(), op);           //是否至少一个满足某准则
    none_of(v1.begin(), v1.end(), op);          //是否无元素满足某准则

    //更易型算法
    copy(v1.begin(), v1.end(), v2.end());
    copy_if(v1.begin(), v1.end(), v2.end(), op);
    copy_n(v1.begin(), 42, v2.end());           //复制n个元素
    copy_backward(v1.begin(), v1.end(), v2.end());        //反向复制某区间
    move(v1.begin(), v1.end(), v2.end());
    move_backward(v1.begin(), v1.end(), v2.end());
    transform(v1.begin(), v1.end(), v2.end(), op);            //改动并复制元素，将两个区间的元素合并
    merge(v1.begin(),v1.end(), v2.begin(), v2.end(), vec.begin());            //合并两区间
    swap_ranges(v1.begin(), v1.end(),v2.begin());      //交换两区间
    fill(v1.begin(), v1.end(), 42);         //以给定值替换每个元素
    fill_n(v1.begin(), 4, 42);           //以给定值替换n个元素
    generate(v1.begin(), v1.end(), op);         //以某项操作的结果替换每个元素
    generate_n(v1.begin(), 42, op);           //以某项操作结果替换n个元素
    iota(vec.begin(), vec.end(), 42);             //将所有元素以一系列的递增值取代
    replace(v1.begin(), v1.end(), 1, 42);          
    replace_if(v1.begin(), v1.end(), op, 42);
    replace_copy(v1.begin(), v1.end(),v2.begin(), 1, 42);
    replace_copy_if(v1.begin(), v1.end(),v2.end(), op, 42);

    //移除型算法
    remove(v1.begin(), v1.end(), 1);
    remove_if(v1.begin(), v1.end(), op);
    remove_copy(v1.begin(), v1.end(),v2.end(), 1);
    remove_copy_if(v1.begin(), v1.end(), v2.end(),op);
    unique(v1.begin(), v1.end());           //移除毗邻的重复元素
    unique_copy(v1.begin(), v1.end(), v2.end());          //移除毗邻的重复元素，并复制到他处

    //变序型算法
    reverse(v1.begin(), v1.end());
    reverse_copy(v1.begin(), v1.end(), v2.end());
    rotate(v1.begin(), v1.begin() + 1, v1.end());           //旋转元素次序
    rotate_copy(v1.begin(), v1.begin() + 1, v1.end(), v2.begin());
    next_permutation(v1.begin(), v1.end());         //得到元素的下一个排列次序   下一个排列次序：排列成当前序列的下一步
    prev_permutation(v1.begin(), v1.end());         //得到元素的上个排列次序
    default_random_engine eng;
    shuffle(v1.begin(), v1.end(), eng);          //将元素的次序随机打乱
    partition(v1.begin(), v1.end(), op);            //改变元素次序，使满足某准则的元素移到前面
    stable_partition(v1.begin(), v1.end(), op);     //同上，但保持相对位置
    partition_copy(v1.begin(), v1.end(), v2.end(), vec.begin(), op);

    //排序算法
    sort(v1.begin(), v1.end());        
    stable_sort(v1.begin(), v1.end());
    partial_sort(v1.begin(), v1.begin() + 3, v1.end());     //排序前n个元素
    partial_sort_copy(v1.begin(), v1.begin() + 3, v1.end(), v2.end());
    nth_element(v1.begin(), v1.begin() + 3, v1.end());          //根据第n个位置进行排序          
    make_heap(v1.begin(), v1.end());            //某区间元素转换成堆
    push_heap(v1.begin(), v1.end(), 42);            //插入堆
    pop_heap(v1.begin(), v1.end(), 42);             //移除堆
    sort_heap(v1.begin(), v1.end());            //对堆进行排序（排序完不再是堆）
    is_sorted(v1.begin(), v1.end());     
    is_sorted_until(v1.begin(), v1.end());          //返回第一个破坏排序状态的元素
    is_partitioned(v1.begin(), v1.end(), op);           
    partition_point(v1.begin(), v1.end(), op);          //返回区间的分割点，它把区间分割成满足和不满足某准则的两组
    is_heap(v1.begin(), v1.end());      
    is_heap_until(v1.begin(), v1.end());       

    //已排序区间算法
    lower_bound(v1.begin(), v1.end(), 42);          //查找第一个大于等于给定值的元素
    upper_bound(v1.begin(), v1.end(), 42);              //查找第一个大于给定值的元素
    equal_range(v1.begin(), v1.end(), 42);          //返回等于给定值的所有元素的区间
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vec.begin());            
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), vec.begin());            //求两区间的并集
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), vec.begin());         //求两区间交集
    set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), vec.begin());           //求位于第一区间但不在第二区间的所有元素，并形成一个已排序区间
    set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), vec.begin());         //找出只出现于两区间之一的所有元素，并形成一个已排序区间
    inplace_merge(v1.begin(), v1.begin() + 3, v1.end());            //将两个连贯的已排序区间合并

    //数值算法
    accumulate(v1.begin(), v1.end(), 42);           //结合所有元素之和
    inner_product(v1.begin(), v1.end(), v2.begin(), 42);            //结合两区间内的所有元素内积
    adjacent_difference(v1.begin(), v1.end(), v2.begin());          //将每个元素减前一个元素
    partial_sum(v1.begin(), v1.end(), v2.begin());           //将每个元素加前一个元素     
}