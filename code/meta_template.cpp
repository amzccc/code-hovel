#include <iostream>

using namespace std;

// 1.编译阶段只能计算整型和布尔型

template<bool flag>
struct Bool {
    static constexpr bool value{ flag };
};

template<int N>
struct Int
{
    static constexpr int value = N;
};

/**
 *@brief 求斐波那契数
 * 
 * @tparam N 
 */
template<int N>
struct Feb {
    static constexpr int value = Feb<N - 1>::value + Feb<N - 2>::value;
};

// 特化
template<>
struct Feb<0>
{
    static constexpr int value = 1;
};

// 特化
template<>
struct Feb<1>
{
    static constexpr int value = 1;
};

// 2.字符串 因为编译阶段只能存整型，不能存字符串，那就把字符串拆开，一个字符一个字符存储
template<char ...C>
struct String {
    static constexpr char const value[sizeof...(C) + 1]{ C..., '\0' };
};

// 3.基础类型组合成高级类型，并且支持嵌套，这样就实现了自定义类型
template<typename T, typename U>
struct Pair{
    using type_fst = T;
    using type_scd = U;
    using value_type_fst = decltype(T::value);
    using value_type_scd = decltype(U::value);
    static constexpr value_type_fst value1 = T::value;
    static constexpr value_type_scd value2 = U::value;
};

template<typename T>
struct Fst {
    using type = T::type_fst;
    static constexpr typename T::value_type_fst value = T::value1;
};

template<typename T>
struct Scd {
    using type = T::type_scd;
    static constexpr typename T::value_type_fst value = T::value2;
};

// 通过变参实现了列表
template<typename T, typename ...Args>
struct List {
    using cur = T;
    using next = List<Args...>;
};

template<typename T>
struct List<T> {
    using cur = T;
    using next = nullptr_t;
};

/* ==============================================================================*/
int main() {
    cout << Bool<true>::value << endl;
    cout << Int<10>::value << endl;
    cout << Feb<7>::value << endl;
    cout << String<'h', 'e', 'l', 'l', 'o'>::value << endl;

    using Pr = Pair<Int<1>, Int<2>>;    // 两个整型的组合类型
    Fst<Pr> fst;    // 声明了一个类型是Pr第一个类型的对象，默认值是组合类型定义时的默认值
    cout << fst.value << endl;
    Scd<Pr> scd;    // 声明了一个类型是Pr第二个类型的对象，同上
    cout << scd.value << endl;
    
    using List = List<Bool<true>, Int<3>, Feb<4>, String<'w', 'o', 'r', 'l', 'd'>>;
    cout << boolalpha << List::cur::value << endl;
    cout << List::next::cur::value << endl;
    cout << List::next::next::cur::value << endl;
    cout << List::next::next::next::cur::value << endl;


    return EXIT_SUCCESS;
}