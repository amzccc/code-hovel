#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <limits>
#include <vector>
#include <thread>

using std::cout;
using std::endl;


template <typename T>
class MyAllocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using void_pointer = void*;
    using const_void_pointer = const void*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    template<typename U>
    struct rebind {
        using other = MyAllocator<U>;
    };

public:
    MyAllocator() = default;

    ~MyAllocator() = default;

public:
    pointer allocate(size_type size) {
        cout << "allocate type:" << typeid(value_type).name() << ", size:"<< size << endl;
        return static_cast<pointer>(operator new(sizeof(value_type) * size));
    }

    pointer allocate(size_type size, const_void_pointer hint) {
        cout << "reload allocate\n";
        return allocate(size);
    }

    void deallocate(pointer p, size_type size) {
        cout << "deallocate " << p << endl;
        operator delete(p);
    }

    // template<typename U, typename... Args>
    // void construct(U* p, Args&&... args) {
    //     cout << "construct" << endl;
    //     new(p) U(std::forward<Args>(args)...);
    // }

    // template<typename U, typename... Args>
    // void destroy(U* p) {
    //     cout << "destroy" << endl;
    //     p->~U();
    // }

    // size_type max_size() const {
    //     return std::numeric_limits<size_type>::max();
    // }
};

template<typename T>
using Vector = std::vector<T, MyAllocator<T>>;

int main() {
    {
        
        Vector<int> vec(2, 0);
        cout << "capacity: " << vec.capacity() << endl;
        vec.push_back(42);
        cout << "capacity: " << vec.capacity() << endl;
    }
    std::cin.get();

    return 0;
}