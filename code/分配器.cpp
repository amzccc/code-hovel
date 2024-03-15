#include <vector>
#include <map>
#include <iostream>
#include <cstddef>      //size_t


using namespace std;

template <typename T>
class MyAlloc {
  public:
    //定义类型
    typedef T value_type;
    //构造函数，因为没有状态所以什么也不用做
    MyAlloc() noexcept {
    
    }
    template <typename U>
    MyAlloc(const MyAlloc<U> &) noexcept {
        //no state to copy
    }
    //分配但不初始化T的元素
    T* allocate(std::size_t num) {
        return static_cast<T*>(::operator new(num * sizeof(T)));
    }
    //回收删除元素的空间
    void deallocate(T* p, std::size_t num) {
        //回收全局删除的内存
        ::operator delete(p);
    }
};

//
template<typename T1, typename T2>
bool operator == (const MyAlloc<T1> &, const MyAlloc<T2> &) noexcept {
    return true;
}

template<typename T1, typename T2>
bool operator != (const MyAlloc<T1> &, const MyAlloc<T2> &) noexcept {
    return false;
}

int main() 
{

}